#ifndef __TPC_SERIAL_DRIVER_HPP
#define __TPC_SERIAL_DRIVER_HPP

#include <stdint.h>

namespace TPC {
  namespace SerialDriver {
    void init();
    void write(uint8_t value);
  }
}

#endif
