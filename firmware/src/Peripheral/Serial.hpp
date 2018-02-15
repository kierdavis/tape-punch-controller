#ifndef __TPC_PERIPHERAL_SERIAL_HPP
#define __TPC_PERIPHERAL_SERIAL_HPP

#include <stdint.h>
#include <avr/pgmspace.h>

#define SERIAL_WRITE(STR) { \
  static const char str[] PROGMEM = STR; \
  Peripheral::Serial::writeStringP(str); \
}

namespace Peripheral {
  namespace Serial {
    void init();
    void write(uint8_t value);
    void writeStringP(PGM_P str);
    void writeHex4(uint8_t val);
    void writeHex8(uint8_t val);
  }
}

#endif
