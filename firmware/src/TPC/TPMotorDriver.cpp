#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#include "TPC/TPMotorDriver.hpp"

static volatile PORT_t * const PORT = &PORTE;
static uint8_t constexpr PIN = 6;
static uint8_t constexpr PIN_MASK = _BV(PIN);

void TPC::TPMotorDriver::init() {
  // Configure pin as an output.
  PORT->DIRSET = PIN_MASK;
  // Set pin low.
  PORT->OUTCLR = PIN_MASK;
}

void TPC::TPMotorDriver::on() {
  PORT->OUTSET = PIN_MASK;
}

void TPC::TPMotorDriver::off() {
  PORT->OUTCLR = PIN_MASK;
}

bool TPC::TPMotorDriver::isOn() {
  return PORT->OUT & PIN_MASK;
}
