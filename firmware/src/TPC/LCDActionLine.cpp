#include <stdint.h>

#include <avr/pgmspace.h>

#include "TPC/LCDActionLine.hpp"
#include "TPC/LCDDriver.hpp"

static void writeChar(char c, uint8_t * column_p) {
  TPC::LCDDriver::writeData(c);
  (*column_p)++;
}

void TPC::LCDActionLine::set(PGM_P left, PGM_P right) {
  TPC::LCDDriver::setCursorPos(1, 0);
  uint8_t column = 0;

  if (left != nullptr) {
    while (column < 8) {
      char c = pgm_read_byte(left++);
      if (c == '\0') { break; }
      writeChar(c, &column);
    }
  }

  if (right != nullptr) {
    uint8_t rightStart = 16 - strlen_P(right);
    while (column < rightStart) {
      writeChar(' ', &column);
    }

    while (column < 16) {
      char c = pgm_read_byte(right++);
      if (c == '\0') { break; }
      writeChar(c, &column);
    }
  }

  while (column < 16) {
    writeChar(' ', &column);
  }
}
