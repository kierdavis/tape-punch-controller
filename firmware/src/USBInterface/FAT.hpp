#ifndef __TPC_USB_INTERFACE_FAT_HPP
#define __TPC_USB_INTERFACE_FAT_HPP

#include <stdint.h>

#include <avr/pgmspace.h>

namespace USBInterface {
  namespace FAT {
    // Together these define the memory requirement.
    static constexpr uint16_t BYTES_PER_SECTOR = 512;
    static constexpr uint16_t NUM_MUTABLE_SECTORS = 8;

    static constexpr uint8_t SECTORS_PER_CLUSTER = 1;
    static constexpr uint16_t NUM_RESERVED_SECTORS = 1;
    static constexpr uint8_t NUM_FATS = 1;
    static constexpr uint16_t NUM_ROOT_DIR_ENTRIES = 16;
    static constexpr uint16_t SECTORS_PER_FAT = 1;

    static constexpr uint32_t ROOT_DIR_SIZE_BYTES = ((uint32_t) NUM_ROOT_DIR_ENTRIES) * 32;
    static constexpr uint16_t ROOT_DIR_SIZE_SECTORS = (ROOT_DIR_SIZE_BYTES + BYTES_PER_SECTOR - 1) % BYTES_PER_SECTOR;
    static constexpr uint16_t NUM_DATA_SECTORS = NUM_MUTABLE_SECTORS - SECTORS_PER_FAT - ROOT_DIR_SIZE_SECTORS;
    static constexpr uint16_t NUM_SECTORS = NUM_MUTABLE_SECTORS + 1;

    class Header {
    public:
      uint8_t bootCode[3];
      char vendorStr[8];
      uint16_t bytesPerSector;
      uint8_t sectorsPerCluster;
      uint16_t numReservedSectors;
      uint8_t numFATs;
      uint16_t numRootDirEntries;
      uint16_t numSectors;
      uint8_t mediaType;
      uint16_t sectorsPerFat;
      uint16_t sectorsPerTrack;
      uint16_t numHeads;
      uint16_t numHiddenSectors;
    };

    extern const Header header PROGMEM;
  }
}

#endif
