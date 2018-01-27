#ifndef __TPC_PERIPHERAL_SERIAL_HPP
#define __TPC_PERIPHERAL_SERIAL_HPP

#include <stdint.h>
#include <avr/pgmspace.h>

namespace Peripheral {
  namespace Serial {
    void init();
    void write(uint8_t value);
    void writeStringP(PGM_P str);
  }
}

#endif
