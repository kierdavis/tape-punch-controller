#ifndef __UTIL_MAYBE_HPP
#define __UTIL_MAYBE_HPP

#include <stdbool.h>
#include <stdint.h>

namespace Util {
  namespace Maybe {
    class Uint8 {
    public:
      bool hasValue;
      uint8_t value;
      Uint8(bool _hasValue = false, uint8_t _value = 0)
        : hasValue(_hasValue), value(_value) {}
    };
  }
}

#endif
