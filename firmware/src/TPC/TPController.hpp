#ifndef __TPC_TP_CONTROLLER_HPP
#define __TPC_TP_CONTROLLER_HPP

#include <stdbool.h>
#include <stdint.h>

#include "TPC/Filesystem.hpp"

namespace TPC {
  namespace TPController {
    void init();
    void setPrintJob_IE(TPC::Filesystem::Reader reader, uint16_t length);
    void setFeedOutJob_IE();
    void clearJob_IE();
    bool readNoTapeSensor();
    bool readLowTapeSensor();
    void serviceTask_IE();

    namespace Hooks {
      void energiseSolenoids_ID();
      void deenergiseSolenoids_ID();
    }
  }
}

#endif
