#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

#include "TPC/BlockStorage.hpp"
#include "TPC/FileSelector.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"

using namespace TPC::Filesystem;

static constexpr uint8_t BOOT_SECTOR = 0;
static constexpr uint8_t FAT_SECTOR = BOOT_SECTOR + NUM_RESERVED_SECTORS;
static constexpr uint8_t ROOT_DIR_SECTOR = FAT_SECTOR + SECTORS_PER_FAT*NUM_FATS;

const TPC::Filesystem::Header TPC::Filesystem::header PROGMEM = {
  // Assembled from x86 code:
  //   loop:  hlt
  //          jmp short loop
  .bootCode = {0xF4, 0xEB, 0xFD},
  .vendorStr = {'S','O','T','O','N','U','N','I'},
  .bytesPerSector = BYTES_PER_SECTOR,
  .sectorsPerCluster = SECTORS_PER_CLUSTER,
  .numReservedSectors = NUM_RESERVED_SECTORS,
  .numFATs = NUM_FATS,
  .numRootDirEntries = NUM_ROOT_DIR_ENTRIES,
  .reserved1 = 0,
  .mediaType = MEDIA_TYPE,
  .sectorsPerFat = SECTORS_PER_FAT,
  .sectorsPerTrack = 0,
  .numHeads = 0,
  .numHiddenSectors = 0,
  .numSectors = NUM_SECTORS,
  .driveNumber = 0x00, // first removable media
  .reserved2 = 0,
  .extendedBootSignature = 0x29, // a magic number
  .volumeID = {0x12, 0x34, 0x56, 0x78},
  .volumeLabel = {'T','A','P','E',' ','P','U','N','C','H',' '},
  .fsTypeStr = {'F','A','T','1','2',' ',' ',' '},
};

static void scanFile(DirectoryEntry * entry) {
  TPC::FileSelector::add(entry);
  LOG("[Filesystem]   discovered file ", entry);
}

static void scanDirectory(uint8_t cluster) {
  Reader reader(cluster);

  static constexpr char END_OF_DIR_MARKER = '\x00';
  static constexpr char UNOCCUPIED_MARKER = '\xE5';

  static constexpr uint8_t LFN_ATTRS = 0x0F;
  static constexpr uint8_t SUBDIR_ATTR = 0x10;

  bool endOfDirReached = false;
  while (!endOfDirReached && !reader.eof()) {
    DirectoryEntry * entry = (DirectoryEntry *) reader.pointer();
    switch (entry->name[0]) {
      case END_OF_DIR_MARKER: {
        endOfDirReached = true;
        break;
      }
      case UNOCCUPIED_MARKER: {
        break;
      }
      default: {
        const uint8_t attributes = entry->attributes;
        if (attributes == LFN_ATTRS) {
          // This entry is a VFAT long filename prefix.
        }
        else if (attributes & SUBDIR_ATTR) {
          // This entry is for a subdirectory.
          scanDirectory(entry->startCluster + NUM_RESERVED_SECTORS);
        }
        else {
          // This entry is for a file.
          scanFile(entry);
        }
        break;
      }
    }
    reader.advance(sizeof(DirectoryEntry));
  }
}

static uint16_t readFATEntry(const uint16_t index) {
  uint8_t * const fat = TPC::BlockStorage::get(FAT_SECTOR);
  const uint16_t pairIndex = index / 2;
  uint8_t * const pair = &fat[pairIndex * 3];
  if (index % 2 == 0) {
    // First half of pair.
    // Low eight bits stored in pair[0].
    // High four bits stored in low nibble of pair[1].
    uint16_t lo = (uint16_t) pair[0];
    uint16_t hi = (uint16_t) (pair[1] & 0x0F);
    return (hi << 8) | lo;
  } else {
    // Second half of pair.
    // Low four bits stored in high nibble of pair[1].
    // High eight bits stored in pair[2].
    uint16_t lo = (uint16_t) (pair[1] & 0xF0);
    uint16_t hi = (uint16_t) pair[2];
    return (hi << 4) | (lo >> 4);
  }
}

static void writeFATEntry(const uint16_t index, const uint16_t val) {
  uint8_t * const fat = TPC::BlockStorage::get(FAT_SECTOR);
  const uint16_t pairIndex = index / 2;
  uint8_t * const pair = &fat[pairIndex * 3];
  if (index % 2 == 0) {
    // First half of pair.
    // Low eight bits stored in pair[0].
    // High four bits stored in low nibble of pair[1].
    pair[0] = val & 0xFF;
    pair[1] = (pair[1] & 0xF0) | ((val >> 8) & 0x0F);
  } else {
    // Second half of pair.
    // Low four bits stored in high nibble of pair[1].
    // High eight bits stored in pair[2].
    pair[1] = (pair[1] & 0x0F) | ((val << 4) & 0xF0);
    pair[2] = (val >> 4) & 0xFF;
  }
}

void TPC::Filesystem::init() {
  writeFATEntry(0, 0xF00 | MEDIA_TYPE);
  writeFATEntry(1, 0xFFF);
}

void TPC::Filesystem::scanFilesystem() {
  LOG("[Filesystem] scanning...");
  TPC::FileSelector::reset();
  scanDirectory(ROOT_DIR_SECTOR);
  LOG("[Filesystem] scan complete");
}

// Always reports EOF.
TPC::Filesystem::Reader::Reader()
  : cluster(0xFFF), offset(0) {}

TPC::Filesystem::Reader::Reader(uint16_t _cluster)
  : cluster(_cluster), offset(0) {}

bool TPC::Filesystem::Reader::eof() const {
  return cluster >= 0xFF8 && cluster <= 0xFFF;
}

const uint8_t * TPC::Filesystem::Reader::pointer() const {
  if (eof()) {
    return nullptr;
  }
  const uint8_t * const clusterData = TPC::BlockStorage::get(cluster);
  return &clusterData[offset];
}

uint16_t TPC::Filesystem::Reader::usableLength() const {
  if (eof()) {
    return 0;
  }
  return BYTES_PER_CLUSTER - offset;
}

void TPC::Filesystem::Reader::advance(uint16_t amount) {
  while (amount >= usableLength()) {
    amount -= usableLength();
    cluster = readFATEntry(cluster);
    offset = 0;
  }
  offset += amount;
}
