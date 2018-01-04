#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "Config.hpp"
#include "TapePunch.hpp"
#include "TapePunchTimer.hpp"

// Compare match A energises the solenoids.
// Compare match B deenergises the solenoids.
// Overflow indicates that the period between sync pulses was too long.

static uint8_t encodePrescaler() {
  switch (Config::tapePunchTimerPrescaler) {
  case 1:
    return _BV(CS00);
  case 8:
    return _BV(CS01);
  case 64:
    return _BV(CS01) | _BV(CS00);
  case 256:
    return _BV(CS02);
  case 1024:
    return _BV(CS02) | _BV(CS00);
  default:
    // Fall back to fastest option (resulting in shortest solenoid pulse time,
    // hence safest).
    return _BV(CS00);
  }
}

void TapePunchTimer::init() {
  // WGM0 = 000 (normal mode)
  // COM0A = 00 (OC0A output pin disabled)
  // COM1A = 00 (OC1A output pin disabled)
  TCCR0A = 0;
  // CS0 = 000 (timer disabled)
  // WGM0 = 000
  TCCR0B = 0;
  // TOIE0 = 1 (interrupt on timer overflow)
  // OCIE0A = 1 (interrupt on compare match A)
  // OCIE0B = 1 (interrupt on compare match B)
  TIMSK0 = _BV(OCIE0B) | _BV(OCIE0A) | _BV(TOIE0);
  // Compare match levels.
  OCR0A = Config::energiseCount;
  OCR0B = Config::deenergiseCount;
}

void TapePunchTimer::start() {
  // Reset the counter value.
  TCNT0 = 0;
  // Start the timer by setting the clock source according to the prescaler
  // selection.
  TCCR0B = encodePrescaler();
}

void TapePunchTimer::stop() {
  // Set the timer's clock source to "none".
  TCCR0B = 0;
}

ISR(TIMER0_COMPA_vect) {
  TapePunch::Callbacks::energiseSolenoids();
}

ISR(TIMER0_COMPB_vect) {
  TapePunch::Callbacks::deenergiseSolenoids();
}

ISR(TIMER0_OVF_vect) {
  TapePunchTimer::stop();
  TapePunch::Callbacks::flagSyncTimeout();
}
