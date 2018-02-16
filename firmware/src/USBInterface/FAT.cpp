#include <avr/pgmspace.h>

#include "Peripheral/Serial.hpp"
#include "USBInterface/BlockStorage.hpp"
#include "USBInterface/FAT.hpp"

using namespace USBInterface::FAT;

static constexpr uint8_t BOOT_SECTOR = 0;
static constexpr uint8_t FAT_SECTOR = 1;
static constexpr uint8_t ROOT_DIR_SECTOR = 2;

const USBInterface::FAT::Header USBInterface::FAT::header PROGMEM = {
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
  .numSectors = NUM_SECTORS,
  .mediaType = 0xF8,
  .sectorsPerFat = SECTORS_PER_FAT,
  .sectorsPerTrack = 0,
  .numHeads = 0,
  .numHiddenSectors = 0
};

typedef struct {
  char name[8];
  char extension[3];
  uint8_t attributes;
  uint8_t reserved;
  uint8_t createTime[5];
  uint8_t accessTime[2];
  uint16_t permissions;
  uint8_t modifiedTime[4];
  uint16_t startCluster;
  uint32_t size;
} DirectoryEntry;
static_assert(sizeof(DirectoryEntry) == 32, "DirectoryEntry should be 32 bytes long");

static void printPaddedStr(const char * const str, const uint8_t maxLen) {
  uint8_t len = maxLen;
  while (len != 0 && str[len-1] == ' ') {
    len--;
  }
  for (uint8_t i = 0; i < len; i++) {
    Peripheral::Serial::write(str[i]);
  }
}

static void printFilename(DirectoryEntry * entry) {
  printPaddedStr(&entry->name[0], 8);
  Peripheral::Serial::write('.');
  printPaddedStr(&entry->extension[0], 3);
}

static void scanFile(DirectoryEntry * entry) {
  SERIAL_WRITE("[FAT] Found file: ");
  printFilename(entry);
  SERIAL_WRITE("\r\n");
}

static void scanDirectory(uint8_t * const clusterData) {
  static constexpr char END_OF_DIR_MARKER = '\x00';
  static constexpr char UNOCCUPIED_MARKER = '\xE5';

  static constexpr uint8_t LFN_ATTRS = 0x0F;
  static constexpr uint8_t SUBDIR_ATTR = 0x10;

  DirectoryEntry * currentEntry = (DirectoryEntry *) clusterData;
  bool looping = true;
  while (looping) {
    switch (currentEntry->name[0]) {
      case END_OF_DIR_MARKER: {
        looping = false;
        break;
      }
      case UNOCCUPIED_MARKER: {
        break;
      }
      default: {
        const uint8_t attributes = currentEntry->attributes;
        if (attributes == LFN_ATTRS) {
          // This entry is a VFAT long filename prefix.
        }
        else if (attributes & SUBDIR_ATTR) {
          // This entry is for a subdirectory.
          uint8_t * const subdirClusterData =
            USBInterface::BlockStorage::get(currentEntry->startCluster);
          scanDirectory(subdirClusterData);
        }
        else {
          // This entry is for a file.
          scanFile(currentEntry);
        }
        break;
      }
    }
  }
}

void USBInterface::FAT::scanFilesystem() {
  SERIAL_WRITE("[FAT] Scanning...\r\n");
  uint8_t * const clusterData = USBInterface::BlockStorage::get(ROOT_DIR_SECTOR);
  scanDirectory(clusterData);
}
