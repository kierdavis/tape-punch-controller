#ifndef __TAPEPUNCH_HPP
#define __TAPEPUNCH_HPP

#include <stdint.h>

namespace TapePunch {
  // Initialise the child modules: Solenoids, FeedbackSignal and TapePunchTimer.
  void init();

  // Provide a buffer of data to be written onto the tape asynchronously. If
  // there are still pending bytes from a previous call to setDataSource that
  // haven't been punched yet, they will be lost.
  void setDataSource(uint8_t *pointer, uint16_t length);

  // Returns the number of bytes from the last buffer provided to setDataSource
  // that are still waiting to be punched.
  uint16_t getPending();

  namespace Callbacks {
    // Called by FeedbackSignal whenever a synchronisation pulse is received.
    // Resets the tape punch timer.
    // Always called inside an interrupt service routine.
    void sync();

    // Called by TapePunchTimer whenever it's time to energise the solenoids.
    // Always called inside an interrupt service routine.
    void energiseSolenoids();

    // Called by TapePunchTimer whenever it's time to deenergise the solenoids.
    // Always called inside an interrupt service routine.
    void deenergiseSolenoids();

    // Called by TapePunchTimer whenever it's been too long since the last sync
    // pulse.
    // Always called inside an interrupt service routine.
    void flagSyncTimeout();
  }
}

#endif
