#ifndef __TPC_APPLICATION_HPP
#define __TPC_APPLICATION_HPP

#include <stdbool.h>
#include <stdint.h>

namespace TPC {
  namespace Application {
    enum class State : uint8_t {
      IDLE,
      IDLE_NO_TAPE_WARNING,
      IDLE_LOW_TAPE_WARNING,
      PRINT,
    };

    void init();
    State getState_IE();
    void returnToIdle_IE();
    void tryStartPrinting_IE(bool ignoreLowTape = false);
    void stopPrinting_IE();
    void selectNextFile_IE();
    void printingComplete_IE();
  }
}

#endif
