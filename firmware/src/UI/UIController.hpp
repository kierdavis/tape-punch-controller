#ifndef __TPC_UI_UI_CONTROLLER_HPP
#define __TPC_UI_UI_CONTROLLER_HPP

namespace UI {
  namespace UIController {
    void init();

    namespace Hooks {
      void confirm();
      void cancel();
      void both();
    }
  }
}

#endif
