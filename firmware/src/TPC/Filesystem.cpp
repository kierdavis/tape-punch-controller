#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

#include "TPC/BlockStorage.hpp"
#include "TPC/FileSelector.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"
#include "TPC/UI.hpp"

using namespace TPC::Filesystem;

static const BlockNumber BOOT_SECTOR = BlockNumber::fromBlock(0);
static const BlockNumber FAT_SECTOR = BlockNumber::fromSector(0);
static const BlockNumber ROOT_DIR_SECTOR = BlockNumber::fromSector(SECTORS_PER_FAT*NUM_FATS);

uint8_t TPC::Filesystem::DirectoryEntry::formatName(char * buffer, uint8_t bufferLen) {
  // Leave room for a null terminator.
  uint8_t usableBufferLen = bufferLen - 1;

  uint8_t nameLen = 8;
  while (nameLen > 0 && name[nameLen-1] == ' ') {
    nameLen--;
  }
  uint8_t extLen = 3;
  while (extLen > 0 && extension[extLen-1] == ' ') {
    extLen--;
  }

  uint8_t bufferPos = 0;
  uint8_t namePos = 0;
  while (bufferPos < usableBufferLen && namePos < nameLen) {
    buffer[bufferPos++] = name[namePos++];
  }
  if (bufferPos < usableBufferLen) {
    buffer[bufferPos++] = '.';
  }
  uint8_t extPos = 0;
  while (bufferPos < usableBufferLen && extPos < extLen) {
    buffer[bufferPos++] = extension[extPos++];
  }
  buffer[bufferPos] = '\0';
  return bufferPos;
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

static void initVolumeLabel() {
  static const char label[11] PROGMEM = {'T','A','P','E',' ','P','U','N','C','H',' '};
  DirectoryEntry * entry = (DirectoryEntry *) TPC::BlockStorage::get(ROOT_DIR_SECTOR);
  memcpy_P(entry->name, label, 11);
  entry->attributes = 0x08;
}

void TPC::Filesystem::init() {
  writeFATEntry(0, 0xF00 | MEDIA_TYPE);
  writeFATEntry(1, 0xFFF);
  initVolumeLabel();
}

static void scanFile(DirectoryEntry * entry) {
  TPC::FileSelector::add(entry);
  LOG(DEBUG_VERBOSE, "[Filesystem]   discovered file ", entry);
}

static void scanDirectory(BlockNumber blockNum);

static bool scanEntry(DirectoryEntry * entry) {
  static constexpr char END_OF_DIR_MARKER = '\x00';
  static constexpr char UNOCCUPIED_MARKER = '\xE5';

  static constexpr uint8_t LFN_ATTRS = 0x0F;
  static constexpr uint8_t HIDDEN_ATTR = 0x02;
  static constexpr uint8_t VOLUME_LABEL_ATTR = 0x08;
  static constexpr uint8_t SUBDIR_ATTR = 0x10;

  switch (entry->name[0]) {
    case END_OF_DIR_MARKER: {
      return true;
    }
    case UNOCCUPIED_MARKER: {
      break;
    }
    case '.': {
      // This entry is a hidden file or directory; do nothing.
      break;
    }
    default: {
      const uint8_t attributes = entry->attributes;
      if (attributes == LFN_ATTRS) {
        // This entry is a VFAT long filename prefix.
      }
      else if (attributes & HIDDEN_ATTR) {
        // This entry is a hidden file or directory; do nothing.
      }
      else if (attributes & VOLUME_LABEL_ATTR) {
        // This entry is the volume label; do nothing.
      }
      else if (attributes & SUBDIR_ATTR) {
        // This entry is for a subdirectory.
        scanDirectory(BlockNumber::fromCluster(entry->startCluster));
      }
      else {
        // This entry is for a file.
        scanFile(entry);
      }
      break;
    }
  }

  return false;
}

static void scanDirectory(BlockNumber blockNum) {
  Reader reader(blockNum);
  while (!reader.eof()) {
    DirectoryEntry * entry = (DirectoryEntry *) reader.pointer();
    if (scanEntry(entry)) {
      // End of directory.
      break;
    }
    reader.advance(sizeof(DirectoryEntry));
  }
}

static void scanRootDirectory() {
  DirectoryEntry * entry = (DirectoryEntry *) TPC::BlockStorage::get(ROOT_DIR_SECTOR);
  while (1) {
    if (scanEntry(entry)) {
      // End of directory.
      break;
    }
    entry++;
  }
}

void TPC::Filesystem::scan() {
  LOG(DEBUG, "[Filesystem] scanning");
  TPC::FileSelector::reset();
  scanRootDirectory();
  TPC::UI::refresh_IE();
}

// Always reports EOF.
TPC::Filesystem::Reader::Reader()
  : blockNum(BlockNumber::fromBlock(0)), eofFlag(true), offset(0) {}

TPC::Filesystem::Reader::Reader(BlockNumber _blockNum)
  : blockNum(_blockNum), eofFlag(false), offset(0) {}

bool TPC::Filesystem::Reader::eof() const {
  return eofFlag;
}

const uint8_t * TPC::Filesystem::Reader::pointer() const {
  if (eofFlag) {
    return nullptr;
  }
  const uint8_t * const blockData = TPC::BlockStorage::get(blockNum);
  return &blockData[offset];
}

uint16_t TPC::Filesystem::Reader::usableLength() const {
  if (eofFlag) {
    return 0;
  }
  return BYTES_PER_CLUSTER - offset;
}

void TPC::Filesystem::Reader::advance(uint16_t amount) {
  while (amount >= usableLength()) {
    amount -= usableLength();
    uint16_t entry = readFATEntry(blockNum.toCluster());
    if (entry >= 0xFF8 && entry <= 0xFFF) {
      eofFlag = true;
      return;
    }
    blockNum = BlockNumber::fromCluster(entry);
    offset = 0;
    LOG(DEBUG, "[Filesystem] advanced to block 0x", blockNum.toBlock());
  }
  offset += amount;
}
