#ifndef __TPC_APPLICATION_HPP
#define __TPC_APPLICATION_HPP

namespace TPC {
  namespace Application {
    void init();
    void tick_IE();

    namespace Hooks {
      void confirm_ID();
      void cancel_ID();
      void both_ID();
    }
  }
}

#endif
