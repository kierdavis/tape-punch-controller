#include <avr/io.h>
#include <avr/interrupt.h>

#include "FeedbackSignal.hpp"
#include "Hooks.hpp"

void FeedbackSignal::init() {
  EICRA |= _BV(ISC21) | _BV(ISC20);
  EIMSK |= _BV(INT2);
}

ISR(INT2_vect) {
  Hooks::onFeedbackPulse();
}
