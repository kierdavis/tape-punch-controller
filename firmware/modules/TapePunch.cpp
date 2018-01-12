#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "Config.hpp"
#include "DigitalOutput.hpp"
#include "FeedbackSignal.hpp"
#include "Solenoids.hpp"
#include "TapePunch.hpp"
#include "TapePunchTimer.hpp"

TapePunch::Job::Job(TapePunch::Job::Type type_,
                    uint16_t count_,
                    volatile uint8_t *data_,
                    volatile TapePunch::Job *next_)
  : type(type_), count(count_), data(data_), next(next_) {}

// A variable with static linkage whose values is a volatile pointer to a volatile Job.
static volatile TapePunch::Job * volatile currentJob = nullptr;

static void initEnablePin() {
  DigitalOutput::initPin(Config::enablePin);
  DigitalOutput::setPin(Config::enablePin, false);
}

void TapePunch::init() {
  FeedbackSignal::init();
  Solenoids::init();
  TapePunchTimer::init();
  initEnablePin();
}

void TapePunch::setEnabled(bool state) {
  DigitalOutput::setPin(Config::enablePin, state);
}

void TapePunch::queueJobs(volatile TapePunch::Job *firstJob) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    volatile TapePunch::Job *j = currentJob;
    if (j == nullptr) {
      // Queue is already empty.
      currentJob = firstJob;
    }
    else {
      // Find the last job currently in the queue.
      volatile TapePunch::Job *next = j->next;
      while (next != nullptr) {
        j = next;
        next = j->next;
      }
      // Chain the argument to the last job currently in the queue.
      j->next = firstJob;
    }
  }
}

bool TapePunch::busy() {
  volatile TapePunch::Job *currentJob_;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    currentJob_ = currentJob;
  }
  return currentJob_ != nullptr;
}

void TapePunch::Callbacks::sync() {
  TapePunchTimer::start();
}

void TapePunch::Callbacks::energiseSolenoids() {
  // Always called in an ISR, so we know interrupts are disabled and so there's
  // no need for an ATOMIC_BLOCK.
  volatile TapePunch::Job *currentJob_ = currentJob;
  if (currentJob_ != nullptr) {
    switch (currentJob_->type) {
    case TapePunch::Job::Type::NOP:
      // do nothing
      break;
    case TapePunch::Job::Type::BLANK:
      Solenoids::energise(0);
      break;
    case TapePunch::Job::Type::DATA:
      volatile uint8_t *pointer = currentJob_->data;
      Solenoids::energise(*pointer);
      currentJob_->data = pointer + 1;
      break;
    }
    uint16_t count = currentJob_->count;
    count--;
    if (count == 0) {
      // Job complete, move to next one.
      currentJob = currentJob_->next;
    }
    else {
      // Carry on with same job.
      currentJob_->count = count;
    }
  }
}

void TapePunch::Callbacks::deenergiseSolenoids() {
  Solenoids::deenergise();
}

void TapePunch::Callbacks::flagSyncTimeout() {
  // TODO
}
