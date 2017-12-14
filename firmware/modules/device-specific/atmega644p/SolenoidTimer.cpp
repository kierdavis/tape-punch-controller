#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "Config.hpp"
#include "Solenoids.hpp"
#include "SolenoidTimer.hpp"

// static_assert((Config::solenoidTimerPrescaler == 1)
//            || (Config::solenoidTimerPrescaler == 8)
//            || (Config::solenoidTimerPrescaler == 64)
//            || (Config::solenoidTimerPrescaler == 256)
//            || (Config::solenoidTimerPrescaler == 1024), "Config::solenoidTimerPrescaler invalid; choices are 1, 8, 64, 256 or 1024");

//     f_{interrupt} = f_{cpu} / (prescaler * (1 + timerLevel))
// =>  timerLevel = f_{cpu} / (prescaler * f_{interrupt}) - 1
// =>  timerLevel = (f_{cpu} * T_{interrupt}) / prescaler - 1
static const float maxCount = (F_CPU * Config::solenoidDuration) / Config::solenoidTimerPrescaler - 1;
// static_assert(maxCount < 256, "solenoid timer maximum count is too high; consider increasing Config::solenoidTimerPrescaler");
// static_assert(maxCount >= 16, "solenoid timer maximum count is very low; consider decreasing Config::solenoidTimerPrescaler to improve accuracy");

static const uint8_t maxCountInt = 210; //(uint8_t) maxCount;

static uint8_t encodePrescaler() {
  switch (Config::solenoidTimerPrescaler) {
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
    // Fall back to fastest option (resulting in shortest solenoid pulse time, hence safest).
    return _BV(CS00);
  }
}

void SolenoidTimer::init() {
  // WGM0 = 010 (clear timer on compare match)
  // COM0A = 00 (OC0A output pin disabled)
  // COM1A = 00 (OC1A output pin disabled)
  TCCR0A = _BV(WGM01);
  // CS0 = 000 (timer disabled)
  // WGM0 = 000
  TCCR0B = 0;
  // TOIE0 = 0 (no interrupt on timer overflow)
  // OCIE0A = 1 (interrupt on compare match A)
  // OCIE0B = 0 (no interrupt on compare match B)
  TIMSK0 = _BV(OCIE0A);
  // Compare match A level.
  OCR0A = maxCountInt;
}

void SolenoidTimer::start() {
  // Ensure the timer's counter is cleared.
  TCNT0 = 0;
  // Set clock source (therefore enabling timer).
  TCCR0B = encodePrescaler();
}

void SolenoidTimer::stop() {
  TCCR0B = 0;
}

ISR(TIMER0_COMPA_vect) {
  Solenoids::deactivate();
  SolenoidTimer::stop();
}
