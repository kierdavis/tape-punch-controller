#ifndef __TPC_BLOCK_STORAGE_HPP
#define __TPC_BLOCK_STORAGE_HPP

#include <stdint.h>

#include "TPC/Filesystem.hpp"

namespace TPC {
  namespace BlockStorage {
    static constexpr uint16_t BYTES_PER_BLOCK = TPC::Filesystem::BYTES_PER_SECTOR;
    static constexpr uint16_t NUM_BLOCKS = TPC::Filesystem::NUM_SECTORS;
    static constexpr uint16_t NUM_MUTABLE_BLOCKS = TPC::Filesystem::NUM_MUTABLE_SECTORS;

    void send(const uint8_t addr);
    void receive(const uint8_t addr);
    uint8_t * get(const uint8_t addr);
  }
}

#endif
