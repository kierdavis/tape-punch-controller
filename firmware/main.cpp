#include <stdint.h>

#include <avr/interrupt.h>

#include "FeedbackSignal.hpp"
#include "Hooks.hpp"
#include "Solenoids.hpp"
#include "SolenoidTimer.hpp"

void Hooks::onFeedbackPulse() {
  Solenoids::pulse(0xFF);
}

int main() {
  Solenoids::init();
  SolenoidTimer::init();
  FeedbackSignal::init();

  sei();
  while (1) {}
}
