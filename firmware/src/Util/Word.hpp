#ifndef __TPC_UTIL_WORD_HPP
#define __TPC_UTIL_WORD_HPP

#include <stdint.h>

namespace Util {
  namespace Word {
    void fromLittleEndian(const uint8_t * srcBuffer, uint16_t * destWord);
    void fromLittleEndian(const uint8_t * srcBuffer, uint32_t * destWord);
    void fromBigEndian(const uint8_t * srcBuffer, uint16_t * destWord);
    void fromBigEndian(const uint8_t * srcBuffer, uint32_t * destWord);
    void toLittleEndian(const uint16_t srcWord, uint8_t * destBuffer);
    void toLittleEndian(const uint32_t srcWord, uint8_t * destBuffer);
    void toBigEndian(const uint16_t srcWord, uint8_t * destBuffer);
    void toBigEndian(const uint32_t srcWord, uint8_t * destBuffer);
  }
}

#endif
