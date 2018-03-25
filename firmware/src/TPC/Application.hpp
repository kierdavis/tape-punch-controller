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
      PRINT_LOW_TAPE_WARNING,
      MENU_FEED_OUT,
      FEED_OUT,
    };

    void init();
    State getState_IE();
    void returnToIdle_IE();
    void tryStartPrinting_IE(bool ignoreLowTape = false);
    void stopPrinting_IE();
    void warnNoTapeDuringPrint_IE();
    void warnLowTapeDuringPrint_IE();
    void selectNextFile_IE();
    void printingComplete_IE();
    void openMenu_IE();
    void closeMenu_IE();
    void startFeedOut_IE();
    void stopFeedOut_IE();
  }
}

#endif
