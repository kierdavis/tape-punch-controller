#ifndef __TPC_PERIPHERAL_SOLENOIDS_HPP
#define __TPC_PERIPHERAL_SOLENOIDS_HPP

#include <stdint.h>

namespace Peripheral {
  namespace Solenoids {
    void init();
    void energise(uint8_t codeValue);
    void deenergise();
  }
}

#endif
