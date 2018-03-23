#ifndef __TPC_TP_SENSORS_DRIVER
#define __TPC_TP_SENSORS_DRIVER

#include <stdbool.h>

namespace TPC {
  namespace TPSensorsDriver {
    void init();
    bool readNoTapeSensor();
    bool readLowTapeSensor();
  }
}

#endif
