#ifndef __TPC_TP_JOB_MANAGER_HPP
#define __TPC_TP_JOB_MANAGER_HPP

#include <stdint.h>

#include "TPC/Util.hpp"

namespace TPC {
  namespace TPJobManager {
    void setJob_IE(uint16_t count, const uint8_t * ptr);
    void tick_IE();
    TPC::Util::MaybeUint8 nextByte_ID();
  }
}

#endif
