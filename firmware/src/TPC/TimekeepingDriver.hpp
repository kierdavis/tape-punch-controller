#ifndef __TPC_TIMEKEEPING_DRIVER_HPP
#define __TPC_TIMEKEEPING_DRIVER_HPP

#include <stdint.h>

namespace TPC {
  namespace TimekeepingDriver {
    void init();
    int16_t getCount();
  }
}

#endif
