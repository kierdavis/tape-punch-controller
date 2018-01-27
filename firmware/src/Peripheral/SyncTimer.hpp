#ifndef __TPC_PERIPHERAL_SYNC_TIMER_HPP
#define __TPC_PERIPHERAL_SYNC_TIMER_HPP

namespace Peripheral {
  namespace SyncTimer {
    void init();
    void stop();

    namespace Hooks {
      void sync_ID();
    }
  }
}

#endif
