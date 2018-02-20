#ifndef __TPC_TP_JOB_MANAGER_HPP
#define __TPC_TP_JOB_MANAGER_HPP

#include <stdbool.h>
#include <stdint.h>

namespace TPC {
  namespace TPJobManager {
    class NextByteResult {
    public:
      bool hasByte;
      uint8_t byte;
      NextByteResult(bool _hasByte = false, uint8_t _byte = 0)
        : hasByte(_hasByte), byte(_byte) {}
    };

    void setJob_IE(uint16_t count, const uint8_t * ptr);
    NextByteResult nextByte_ID();
  }
}

#endif
