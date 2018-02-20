#ifndef __TPC_USB_INTERFACE_BLOCK_STORAGE_HPP
#define __TPC_USB_INTERFACE_BLOCK_STORAGE_HPP

#include <stdint.h>

#include "USBInterface/FAT.hpp"

namespace TPC {
  namespace BlockStorage {
    static constexpr uint16_t BYTES_PER_BLOCK = USBInterface::FAT::BYTES_PER_SECTOR;
    static constexpr uint16_t NUM_BLOCKS = USBInterface::FAT::NUM_SECTORS;
    static constexpr uint16_t NUM_MUTABLE_BLOCKS = USBInterface::FAT::NUM_MUTABLE_SECTORS;

    void send(const uint8_t addr);
    void receive(const uint8_t addr);
    uint8_t * get(const uint8_t addr);
  }
}

#endif
