#ifndef __TPC_USB_INTERFACE_FAT_HPP
#define __TPC_USB_INTERFACE_FAT_HPP

#include <stdint.h>

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

    void sendSector(const uint8_t addr);
    void receiveSector(const uint8_t addr);
  }
}

#endif