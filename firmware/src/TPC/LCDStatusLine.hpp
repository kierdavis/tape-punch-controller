#ifndef __TPC_LCD_STATUS_LINE_HPP
#define __TPC_LCD_STATUS_LINE_HPP

#include <avr/pgmspace.h>

namespace TPC {
  namespace LCDStatusLine {
    void clear();
    void append(const char * str);
    void appendP(PGM_P str);
    void finishAppending();
    void scroll();
  }
}

#define SET_LCD_STATUS_LINE(STR) { \
  static const char str[] PROGMEM = STR; \
  TPC::LCDStatusLine::clear(); \
  TPC::LCDStatusLine::appendP(str); \
  TPC::LCDStatusLine::finishAppending(); \
}

#endif
