#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#include "TPC/TPSolenoidsDriver.hpp"

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

void TPC::TPSolenoidsDriver::init() {
  configurePins();
  setPins(0x00, false);
}

void TPC::TPSolenoidsDriver::energise(uint8_t codeValue) {
  setPins(codeValue, true);
}

void TPC::TPSolenoidsDriver::deenergise() {
  setPins(0x00, false);
}
