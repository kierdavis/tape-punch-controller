#ifndef __TPC_TP_JOB_MANAGER_HPP
#define __TPC_TP_JOB_MANAGER_HPP

#include <stdint.h>

#include "Util/Maybe.hpp"

namespace TPC {
  namespace TPJobManager {
    void setJob_IE(uint16_t count, const uint8_t * ptr);
    void tick_IE();
    Util::Maybe::Uint8 nextByte_ID();
  }
}

#endif
