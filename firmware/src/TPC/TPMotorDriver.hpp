#ifndef __TPC_TP_MOTOR_DRIVER_HPP
#define __TPC_TP_MOTOR_DRIVER_HPP

#include <stdbool.h>

namespace TPC {
  namespace TPMotorDriver {
    void init();
    void on();
    void off();
    bool isOn();
  }
}

#endif
