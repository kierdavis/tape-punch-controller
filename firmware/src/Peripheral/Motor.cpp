#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#include "Peripheral/Motor.hpp"

static void configurePin();
static void setPin(bool value);

void Peripheral::Motor::init() {
  configurePin();
  setPin(false);
}

void Peripheral::Motor::on() {
  setPin(true);
}

void Peripheral::Motor::off() {
  setPin(false);
}

// Platform-specific code is below.

#if defined(PLATFORM_IL_MATTO)
  static volatile uint8_t * const DDR = &DDRB;
  static volatile uint8_t * const PORT = &PORTB;
  static uint8_t constexpr PIN = 1;
  static uint8_t constexpr PIN_MASK = _BV(PIN);

  static void configurePin() {
    *DDR |= PIN_MASK;
  }

  static void setPin(bool value) {
    if (value) {
      *PORT |= PIN_MASK;
    } else {
      *PORT &= ~PIN_MASK;
    }
  }

#elif defined(PLATFORM_PCB)
  static volatile PORT_t * const PORT = &PORTE;
  static uint8_t constexpr PIN = 6;
  static uint8_t constexpr PIN_MASK = _BV(PIN);

  static void configurePin() {
    PORT->DIRSET = PIN_MASK;
  }

  static void setPin(bool value) {
    if (value) {
      PORT->OUTSET = PIN_MASK;
    } else {
      PORT->OUTCLR = PIN_MASK;
    }
  }

#else
  #error "invalid or unsupported PLATFORM"
#endif
