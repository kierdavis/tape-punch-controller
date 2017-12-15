#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "Config.hpp"
#include "Solenoids.hpp"
#include "SolenoidTimer.hpp"

// Feedback interrupt starts/resets the timer.
// Solenoids activated at COMPA
// Solenoids deactivated at COMPB
// If overflow is reached, it's been too long since the last feedback interrupt => stop the timer.

static const uint16_t prescaler = 1024;
static const uint8_t activationLevelInt = 31;
static const uint8_t deactivationLevelInt = 84;

// static_assert((prescaler == 1)
//            || (prescaler == 8)
//            || (prescaler == 64)
//            || (prescaler == 256)
//            || (prescaler == 1024), "prescaler invalid; choices are 1, 8, 64, 256 or 1024");

static uint8_t encodePrescaler() {
  switch (prescaler) {
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
  TIMSK0 = _BV(OCIE0B) |_BV(OCIE0A) | _BV(TOIE0);
  // Compare match levels.
  OCR0A = activationLevelInt;
  OCR0B = deactivationLevelInt;


  UCSR0A = 0;
  UCSR0B = _BV(RXCIE0) | _BV(RXEN0);
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
  UBRR0 = (F_CPU / 16) / 9600 - 1;
}

void SolenoidTimer::start() {
  // Ensure the timer's counter is cleared.
  TCNT0 = 0;
  // Set clock source (therefore enabling timer).
  TCCR0B = encodePrescaler();
}

void SolenoidTimer::stop() {
  TCCR0B = 0;
  Solenoids::deactivate();
}



#define BUFFER_SIZE 128
static uint8_t buffer[BUFFER_SIZE];
static uint8_t buffer_rptr = 0;
static uint8_t buffer_wptr = 0;

ISR(USART0_RX_vect) {
  uint8_t value = UDR0;
  if (value & 0x80) {
    buffer[buffer_wptr] = value;
    buffer_wptr = (buffer_wptr + 1) % BUFFER_SIZE;
  }
}

static uint8_t wait = 100;
static uint8_t lead_in = 0;

ISR(TIMER0_COMPA_vect) {
  uint8_t value = 0x00;
  if (wait > 0) {
    wait--;
    return;
  }
  else if (lead_in > 0) {
    lead_in--;
  }
  else if (buffer_rptr != buffer_wptr) {
    value = buffer[buffer_rptr];
    buffer_rptr = (buffer_rptr + 1) % BUFFER_SIZE;
  }
  else {
    return;
  }
  Solenoids::activate(value);
}

ISR(TIMER0_COMPB_vect) {
  Solenoids::deactivate();
}

ISR(TIMER0_OVF_vect) {
  SolenoidTimer::stop();
}
