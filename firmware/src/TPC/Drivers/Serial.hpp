#ifndef __TPC_DRIVERS_SERIAL_HPP
#define __TPC_DRIVERS_SERIAL_HPP

#include <stdint.h>
#include <avr/pgmspace.h>

#define SERIAL_WRITE(STR) { \
  static const char str[] PROGMEM = STR; \
  TPC::Drivers::Serial::writeStringP(str); \
}

namespace TPC {
  namespace Drivers {
    namespace Serial {
      void init();
      void write(uint8_t value);
      void writeNewline();
      void writeStringP(PGM_P str);
      void writeHex4(uint8_t val);
      void writeHex8(uint8_t val);
      void writeHex16(uint16_t val);
    }
  }
}

#endif
