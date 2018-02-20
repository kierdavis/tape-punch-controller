#include <stdint.h>

#include <avr/pgmspace.h>

#include "TPC/TPCoding.hpp"

uint8_t TPC::TPCoding::asciiToEdsac(char c) {
  static const uint8_t letters[26] PROGMEM = {
    /* A */ 0b01100,
    /* B */ 0b01101,
    /* C */ 0b01110,
    /* D */ 0b00011,
    /* E */ 0b10011,
    /* F */ 0b00001,
    /* G */ 0b01011,
    /* H */ 0b00101,
    /* I */ 0b11000,
    /* J */ 0b11010,
    /* K */ 0b11110,
    /* L */ 0b01001,
    /* M */ 0b00111,
    /* N */ 0b00110,
    /* O */ 0b11001,
    /* P */ 0b10000,
    /* Q */ 0b10001,
    /* R */ 0b10100,
    /* S */ 0b11100,
    /* T */ 0b10101,
    /* U */ 0b10111,
    /* V */ 0b01111,
    /* W */ 0b10010,
    /* X */ 0b01010,
    /* Y */ 0b10110,
    /* Z */ 0b11101,
  };

  if (c >= 'A' && c <= 'Z') {
    return pgm_read_byte(&letters[c - 'A']);
  }
  if (c >= 'a' && c <= 'z') {
    return pgm_read_byte(&letters[c - 'a']);
  }
  if (c >= '0' && c <= '9') {
    return 0b10000 + (c - '0');
  }

  switch (c) {
  case '@': // theta
    return 0b00010;
  case '!': // phi
    return 0b00100;
  case '&': // delta
    return 0b01000;
  case '#': // pi
    return 0b11011;
  case '+':
    return 0b00101;
  case '-':
    return 0b00110;
  case '.': // blank
    return 0b00000;
  case '*': // erase/delete
    return 0b11111;
  case '[':
    return TPC::TPCoding::BEGIN_COMMENT;
  case ']':
    return TPC::TPCoding::END_COMMENT;
  default:
    return TPC::TPCoding::UNPRINTABLE;
  }
}
