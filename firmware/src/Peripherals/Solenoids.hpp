#ifndef __TPC_PERIPHERALS_SOLENOIDS_HPP
#define __TPC_PERIPHERALS_SOLENOIDS_HPP

#include <stdint.h>

namespace Peripherals {
  namespace Solenoids {
    void init();
    void energise(uint8_t codeValue);
    void deenergise();
  }
}

#endif
