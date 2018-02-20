#ifndef __TPC_CONTROLLER_TAPE_PUNCH_HPP
#define __TPC_CONTROLLER_TAPE_PUNCH_HPP

#include <stdint.h>

namespace Controller {
  namespace TapePunch {
    void init();
    void setJob_IE(uint16_t length, const uint8_t * buffer = nullptr);

    namespace Hooks {
      void energiseSolenoids_ID();
      void deenergiseSolenoids_ID();
    }
  }
}

#endif
