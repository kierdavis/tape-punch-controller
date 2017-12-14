#include <avr/interrupt.h>
#include <avr/io.h>

#include "Config.hpp"
#include "FeedbackSignal.hpp"
#include "Hooks.hpp"
#include "IO.hpp"

void FeedbackSignal::init() {
  switch (Config::feedbackPin) {
  case IO::ExternalInterruptPin::INT0_:
    EICRA |= _BV(ISC01) | _BV(ISC00);
    EIMSK |= _BV(INT0);
    break;
  case IO::ExternalInterruptPin::INT1_:
    EICRA |= _BV(ISC11) | _BV(ISC10);
    EIMSK |= _BV(INT1);
    break;
  case IO::ExternalInterruptPin::INT2_:
    EICRA |= _BV(ISC21) | _BV(ISC20);
    EIMSK |= _BV(INT2);
    break;
  }
}

ISR(INT0_vect) {
  if (Config::feedbackPin == IO::ExternalInterruptPin::INT0_) {
    Hooks::onFeedbackPulse();
  }
}

ISR(INT1_vect) {
  if (Config::feedbackPin == IO::ExternalInterruptPin::INT1_) {
    Hooks::onFeedbackPulse();
  }
}

ISR(INT2_vect) {
  if (Config::feedbackPin == IO::ExternalInterruptPin::INT2_) {
    Hooks::onFeedbackPulse();
  }
}
