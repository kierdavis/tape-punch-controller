#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#include "Peripheral/Solenoids.hpp"

static void configurePins();
static void setPins(uint8_t codeValue, bool feedValue);

void Peripheral::Solenoids::init() {
  configurePins();
  setPins(0x00, false);
}

void Peripheral::Solenoids::energise(uint8_t codeValue) {
  setPins(codeValue, true);
}

void Peripheral::Solenoids::deenergise() {
  setPins(0x00, false);
}

// Platform-specific code is below.

#if defined(PLATFORM_IL_MATTO)
  static volatile uint8_t * const CODE_DDR = &DDRA;
  static volatile uint8_t * const CODE_PORT = &PORTA;

  static volatile uint8_t * const FEED_DDR = &DDRB;
  static volatile uint8_t * const FEED_PORT = &PORTB;
  static uint8_t constexpr FEED_PIN = 0;
  static uint8_t constexpr FEED_PIN_MASK = _BV(FEED_PIN);

  static void configurePins() {
    *CODE_DDR = 0xFF;
    *FEED_DDR |= FEED_PIN_MASK;
  }

  static void setPins(uint8_t codeValue, bool feedValue) {
    *CODE_PORT = codeValue;
    if (feedValue) {
      *FEED_PORT |= FEED_PIN_MASK;
    } else {
      *FEED_PORT &= ~FEED_PIN_MASK;
    }
  }

#elif defined(PLATFORM_PCB)
  static volatile PORT_t * const CODE_PORT = &PORTF;

  static volatile PORT_t * const FEED_PORT = &PORTA;
  static uint8_t constexpr FEED_PIN = 0;
  static uint8_t constexpr FEED_PIN_MASK = _BV(FEED_PIN);

  static void configurePins() {
    CODE_PORT->DIRSET = 0xFF;
    FEED_PORT->DIRSET = FEED_PIN_MASK;
  }

  static void setPins(uint8_t codeValue, bool feedValue) {
    CODE_PORT->OUT = codeValue;
    if (feedValue) {
      FEED_PORT->OUTSET = FEED_PIN_MASK;
    } else {
      FEED_PORT->OUTCLR = FEED_PIN_MASK;
    }
  }

#else
  #error "invalid or unsupported PLATFORM"
#endif
