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

static uint8_t *volatile bufferPointer = nullptr;
static uint16_t volatile bufferLength = 0;

void TapePunch::init() {
  FeedbackSignal::init();
  Solenoids::init();
  TapePunchTimer::init();

  DigitalOutput::initPin(Config::enablePin);
  DigitalOutput::setPin(Config::enablePin, false);
}

void TapePunch::setEnabled(bool state) {
  DigitalOutput::setPin(Config::enablePin, state);
}

void TapePunch::setDataSource(uint8_t *pointer, uint16_t length) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    bufferPointer = pointer;
    bufferLength = length;
  }
}

uint16_t TapePunch::getPending() {
  uint16_t length;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    length = bufferLength;
  }
  return length;
}

void TapePunch::Callbacks::sync() {
  TapePunchTimer::start();
}

void TapePunch::Callbacks::energiseSolenoids() {
  // Always called in an ISR, so we know interrupts are disabled and so there's
  // no need for an ATOMIC_BLOCK.
  uint16_t length = bufferLength;
  if (length > 0) {
    bufferLength = length - 1;
    uint8_t *pointer = bufferPointer;
    Solenoids::energise(*pointer);
    bufferPointer = pointer + 1;
  }
}

void TapePunch::Callbacks::deenergiseSolenoids() {
  Solenoids::deenergise();
}

void TapePunch::Callbacks::flagSyncTimeout() {
  // TODO
}
