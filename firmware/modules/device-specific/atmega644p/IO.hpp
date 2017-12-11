#ifndef __IO_HPP
#define __IO_HPP

#include <stdint.h>

namespace IO {
  class Port {
  public:
    volatile uint8_t* const DDR;
    volatile uint8_t* const PORT;
    volatile uint8_t* const PIN;

    static const Port A, B, C, D;
  };

  class Pin {
  public:
    const Port &port;
    const uint8_t index;
  };
}

#endif // #ifndef __IO_HPP
