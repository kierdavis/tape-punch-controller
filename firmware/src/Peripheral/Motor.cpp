#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#include "Peripheral/Motor.hpp"

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
