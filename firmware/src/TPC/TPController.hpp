#ifndef __TPC_TP_CONTROLLER_HPP
#define __TPC_TP_CONTROLLER_HPP

#include <stdint.h>

#include "TPC/Filesystem.hpp"

namespace TPC {
  namespace TPController {
    void init();
    bool isOn_IE();
    void setJob_IE(TPC::Filesystem::Reader reader, uint16_t length);
    void clearJob_IE();
    void tick_IE();

    namespace Hooks {
      void energiseSolenoids_ID();
      void deenergiseSolenoids_ID();
    }
  }
}

#endif
