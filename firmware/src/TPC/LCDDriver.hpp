#ifndef __TPC_LCD_DRIVER_HPP
#define __TPC_LCD_DRIVER_HPP

#include <stdint.h>

#include <avr/pgmspace.h>

namespace TPC {
  namespace LCDDriver {
    void init();
    void clear();
    void writeAt(const uint8_t row, const uint8_t col, const char * str);
    void writeAtP(const uint8_t row, const uint8_t col, PGM_P str);
  }
}

#define LCD_WRITE_AT(ROW, COL, STR) { \
  static const char str[] PROGMEM = STR; \
  TPC::LCDDriver::writeAtP(ROW, COL, str); \
}

#endif
