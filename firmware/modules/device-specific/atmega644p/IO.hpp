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

  enum class ExternalInterruptPin {
    // Names INT0/INT1/INT2 conflict with preprocessor macros defined by avr/io.h
    INT0_, INT1_, INT2_
  };
}

#endif // #ifndef __IO_HPP
