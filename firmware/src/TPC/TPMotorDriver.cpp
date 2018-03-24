#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#include "TPC/TPMotorDriver.hpp"

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

void TPC::TPMotorDriver::init() {
  configurePin();
  setPin(false);
}

void TPC::TPMotorDriver::on() {
  setPin(true);
}

void TPC::TPMotorDriver::off() {
  setPin(false);
}

bool TPC::TPMotorDriver::isOn() {
  return PORT->OUT & PIN_MASK;
}
