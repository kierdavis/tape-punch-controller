#ifndef __TPC_LCD_ACTION_LINE_HPP
#define __TPC_LCD_ACTION_LINE_HPP

#include <avr/pgmspace.h>

namespace TPC {
  namespace LCDActionLine {
    void set(PGM_P left, PGM_P right);
  }
}

#define SET_LCD_ACTION_LINE(LEFT, RIGHT) { \
  static const char leftStr[] PROGMEM = "[" LEFT "]"; \
  static const char rightStr[] PROGMEM = "[" RIGHT "]"; \
  TPC::LCDActionLine::set( \
    (sizeof(LEFT) > 1) ? leftStr : nullptr, \
    (sizeof(RIGHT) > 1) ? rightStr : nullptr \
  ); \
}

#endif
