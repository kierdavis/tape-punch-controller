// The TapePunchTimer component encapsulates a hardware timer that is
// synchronised to the rotation of the tape punch's drive shaft.

// Principles of operation:
// * Every time a synchronisation pulse is received, the timer starts counting
//   up from 0.
// * The counting frequency is set such that another synchronisation pulse
//   should be received before the counter reaches its maximum value.
// * As a result, if the counter *does* reach its maximum value, we assume that
//   synchronisation pulses have stopped being received.
// * At a predefined counter level, the solenoids will be energised.
// * Similarly, at another predefined level the solenoids are
//   deenergised.

#ifndef __TAPEPUNCHTIMER_HPP
#define __TAPEPUNCHTIMER_HPP

namespace TapePunchTimer {
  // Initialise the timer, but don't start it.
  void init();

  // Reset and start the timer.
  void start();

  // Stop the timer, if it it running.
  void stop();
}

#endif // __TAPEPUNCHTIMER_HPP
