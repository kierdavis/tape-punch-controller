#ifndef __TPC_UTIL_HPP
#define __TPC_UTIL_HPP

#include <stdbool.h>
#include <stdint.h>

namespace TPC {
  namespace Util {
    uint8_t min(const uint8_t a, const uint8_t b);
    uint16_t min(const uint16_t a, const uint16_t b);

    void fromLittleEndian(const uint8_t * srcBuffer, uint16_t * destWord);
    void fromLittleEndian(const uint8_t * srcBuffer, uint32_t * destWord);
    void fromBigEndian(const uint8_t * srcBuffer, uint16_t * destWord);
    void fromBigEndian(const uint8_t * srcBuffer, uint32_t * destWord);
    void toLittleEndian(const uint16_t srcWord, uint8_t * destBuffer);
    void toLittleEndian(const uint32_t srcWord, uint8_t * destBuffer);
    void toBigEndian(const uint16_t srcWord, uint8_t * destBuffer);
    void toBigEndian(const uint32_t srcWord, uint8_t * destBuffer);

    class MaybeUint8 {
    public:
      bool hasValue;
      uint8_t value;
      MaybeUint8(bool _hasValue = false, uint8_t _value = 0)
        : hasValue(_hasValue), value(_value) {}
    };
  }
}

#endif
