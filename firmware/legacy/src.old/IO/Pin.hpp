#ifndef __TPC_IO_PIN_HPP
#define __TPC_IO_PIN_HPP

#include <stdint.h>

#include "IO/Port.hpp"

namespace IO {
  class Pin {
  public:
    const IO::Port port;
    const uint8_t index;
  };
}

#endif
