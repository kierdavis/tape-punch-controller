#ifndef __TPC_BLOCK_STORAGE_HPP
#define __TPC_BLOCK_STORAGE_HPP

#include <stdint.h>

#include "TPC/BootCode.hpp"
#include "TPC/Filesystem.hpp"

namespace TPC {
  namespace BlockStorage {
    static constexpr uint16_t BYTES_PER_BLOCK = TPC::Filesystem::BYTES_PER_SECTOR;
    static constexpr uint16_t NUM_BLOCKS = TPC::Filesystem::NUM_SECTORS;
    static constexpr uint16_t NUM_MUTABLE_BLOCKS = TPC::Filesystem::NUM_MUTABLE_SECTORS;

    class Header {
    public:
      uint8_t bootJump[3];
      TPC::Filesystem::Header filesystemHeader;
      uint8_t bootCode[TPC_BOOT_CODE_LEN];
    };

    static constexpr Header header = {
      // While this is supposed to be arbitrary x86 code, Windows systems seem
      // to consider a signature that must be matched. Therefore, these three
      // bytes shouldn't be changed from their current values.
      .bootJump = {0xEB, 0x3C, 0x90},
      .filesystemHeader = TPC::Filesystem::header,
      .bootCode = TPC_BOOT_CODE,
    };

    void send(const uint8_t addr);
    void receive(const uint8_t addr);
    uint8_t * get(const uint8_t addr);
  }
}

#endif
