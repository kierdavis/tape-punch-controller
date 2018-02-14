#include <stdint.h>

#include "Util/Word.hpp"

void Util::Word::fromLittleEndian(const uint8_t * srcBuffer, uint16_t * destWord) {
  const uint16_t a = (uint16_t) srcBuffer[0];
  const uint16_t b = (uint16_t) srcBuffer[1];
  *destWord = (b << 8) | a;
}

void Util::Word::fromLittleEndian(const uint8_t * srcBuffer, uint32_t * destWord) {
  const uint32_t a = (uint32_t) srcBuffer[0];
  const uint32_t b = (uint32_t) srcBuffer[1];
  const uint32_t c = (uint32_t) srcBuffer[2];
  const uint32_t d = (uint32_t) srcBuffer[3];
  *destWord = (d << 24) | (c << 16) | (b << 8) | a;
}

void Util::Word::fromBigEndian(const uint8_t * srcBuffer, uint16_t * destWord) {
  const uint16_t a = (uint16_t) srcBuffer[0];
  const uint16_t b = (uint16_t) srcBuffer[1];
  *destWord = (a << 8) | b;
}

void Util::Word::fromBigEndian(const uint8_t * srcBuffer, uint32_t * destWord) {
  const uint32_t a = (uint32_t) srcBuffer[0];
  const uint32_t b = (uint32_t) srcBuffer[1];
  const uint32_t c = (uint32_t) srcBuffer[2];
  const uint32_t d = (uint32_t) srcBuffer[3];
  *destWord = (a << 24) | (b << 16) | (c << 8) | d;
}

void Util::Word::toLittleEndian(const uint16_t srcWord, uint8_t * destBuffer) {
  destBuffer[0] = (uint8_t) srcWord;
  destBuffer[1] = (uint8_t) (srcWord >> 8);
}

void Util::Word::toLittleEndian(const uint32_t srcWord, uint8_t * destBuffer) {
  destBuffer[0] = (uint8_t) srcWord;
  destBuffer[1] = (uint8_t) (srcWord >> 8);
  destBuffer[2] = (uint8_t) (srcWord >> 16);
  destBuffer[3] = (uint8_t) (srcWord >> 24);
}

void Util::Word::toBigEndian(const uint16_t srcWord, uint8_t * destBuffer) {
  destBuffer[0] = (uint8_t) (srcWord >> 8);
  destBuffer[1] = (uint8_t) srcWord;
}

void Util::Word::toBigEndian(const uint32_t srcWord, uint8_t * destBuffer) {
  destBuffer[0] = (uint8_t) (srcWord >> 24);
  destBuffer[1] = (uint8_t) (srcWord >> 16);
  destBuffer[2] = (uint8_t) (srcWord >> 8);
  destBuffer[3] = (uint8_t) srcWord;
}
