#ifndef __TPC_UI_HPP
#define __TPC_UI_HPP

namespace TPC {
  namespace UI {
    void init();
    void refresh_IE();
    void tick_IE();

    namespace Hooks {
      void confirm_ID();
      void cancel_ID();
      void both_ID();
    }
  }
}

#endif
