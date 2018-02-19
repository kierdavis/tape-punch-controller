#ifndef __TPC_TP_TIMER_DRIVER_HPP
#define __TPC_TP_TIMER_DRIVER_HPP

namespace TPC {
  namespace TPTimerDriver {
    void init();
    void stop();

    namespace Hooks {
      void sync_ID();
    }
  }
}

#endif
