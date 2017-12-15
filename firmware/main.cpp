#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "FeedbackSignal.hpp"
#include "Hooks.hpp"
#include "Solenoids.hpp"
#include "SolenoidTimer.hpp"

void Hooks::onFeedbackPulse() {
  SolenoidTimer::start();
}

int main() {
  Solenoids::init();
  SolenoidTimer::init();
  FeedbackSignal::init();

  sei();
  while (1) {}
}
