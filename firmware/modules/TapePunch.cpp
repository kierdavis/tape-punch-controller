#include <stdint.h>
#include <avr/interrupt.h>

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
}

void TapePunch::setDataSource(uint8_t *pointer, uint16_t length) {
  // bufferPointer and bufferLength are used by interrupt service routines
  // (via energiseSolenoids), so we should disable interrupts while we access
  // them here to prevent inconsistent data access.
  cli();
  bufferPointer = pointer;
  bufferLength = length;
  sei();
}

uint16_t TapePunch::getPending() {
  cli();
  uint16_t length = bufferLength;
  sei();
  return length;
}

void TapePunch::Callbacks::sync() {
  TapePunchTimer::start();
}

void TapePunch::Callbacks::energiseSolenoids() {
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
