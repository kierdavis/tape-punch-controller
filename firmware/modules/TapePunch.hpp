#ifndef __TAPEPUNCH_HPP
#define __TAPEPUNCH_HPP

namespace TapePunch {
  // Initialise the child modules: Solenoids, FeedbackSignal and TapePunchTimer.
  void init();

  // Called by FeedbackSignal whenever a synchronisation pulse is received.
  // Resets the tape punch timer.
  void sync();

  // Called by TapePunchTimer whenever it's time to energise the solenoids.
  void energiseSolenoids();

  // Called by TapePunchTimer whenever it's time to deenergise the solenoids.
  void deenergiseSolenoids();

  // Called by TapePunchTimer whenever it's been too long since the last sync
  // pulse.
  void flagSyncTimeout();
}

#endif
