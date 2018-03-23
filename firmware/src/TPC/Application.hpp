#ifndef __TPC_APPLICATION_HPP
#define __TPC_APPLICATION_HPP

#include <stdint.h>

namespace TPC {
  namespace Application {
    enum class State : uint8_t {
      IDLE,
      PRINT,
    };

    void init();
    State getState_IE();
    void startPrinting_IE();
    void stopPrinting_IE();
    void selectNextFile_IE();
    void serviceTask_IE();
  }
}

#endif
