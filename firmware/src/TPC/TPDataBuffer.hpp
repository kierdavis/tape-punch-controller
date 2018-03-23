#ifndef __TPC_TP_DATA_BUFFER_HPP
#define __TPC_TP_DATA_BUFFER_HPP

#include <stdbool.h>
#include <stdint.h>

#include "TPC/Util.hpp"

namespace TPC {
  namespace TPDataBuffer {
    void reset_ID();
    void push_ID(const uint8_t value);
    TPC::Util::MaybeUint8 pop_ID();
    bool full_ID();
  }
}

#endif
