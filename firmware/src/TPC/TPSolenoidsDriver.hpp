#ifndef __TPC_TP_SOLENOIDS_DRIVER_HPP
#define __TPC_TP_SOLENOIDS_DRIVER_HPP

#include <stdint.h>

namespace TPC {
  namespace TPSolenoidsDriver {
    void init();
    void energise(uint8_t codeValue);
    void deenergise();
  }
}

#endif
