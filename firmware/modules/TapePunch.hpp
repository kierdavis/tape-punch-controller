#ifndef __TAPEPUNCH_HPP
#define __TAPEPUNCH_HPP

#include <stdbool.h>
#include <stdint.h>

namespace TapePunch {
  class Job {
  public:
    enum class Type : uint8_t {
      NOP, BLANK, DATA,
    };

    Type type;
    uint16_t count;
    volatile uint8_t *data;
    volatile Job *next;

    Job(Type type_, uint16_t count_, volatile uint8_t *data_ = nullptr, volatile Job *_next = nullptr);
  };

  // Initialise the child modules: Solenoids, FeedbackSignal and TapePunchTimer.
  void init();

  // Turn the tape punch on or off.
  void setEnabled(bool state);

  void setJobs(volatile Job *firstJob);

  bool busy();

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
