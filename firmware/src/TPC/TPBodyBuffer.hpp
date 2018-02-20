#ifndef __TPC_TP_BODY_BUFFER_HPP
#define __TPC_TP_BODY_BUFFER_HPP

#include <stdbool.h>
#include <stdint.h>

#include "Util/Maybe.hpp"

namespace TPC {
  namespace TPBodyBuffer {
    void push_ID(const uint8_t value);
    Util::Maybe::Uint8 pop_ID();
    bool full_ID();
  }
}

#endif
