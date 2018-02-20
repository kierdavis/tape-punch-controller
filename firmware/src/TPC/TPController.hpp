#ifndef __TPC_TP_CONTROLLER_HPP
#define __TPC_TP_CONTROLLER_HPP

#include <stdint.h>

namespace TPC {
  namespace TPController {
    void init();
    bool isOn_IE();
    void setJob_IE(uint16_t length, const uint8_t * buffer = nullptr);
    void tick_IE();

    namespace Hooks {
      void energiseSolenoids_ID();
      void deenergiseSolenoids_ID();
    }
  }
}

#endif
