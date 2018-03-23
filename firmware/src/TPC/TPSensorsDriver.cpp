#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#include "TPC/TPController.hpp"
#include "TPC/TPSensorsDriver.hpp"

static volatile PORT_t * const PORT = &PORTE;
static constexpr uint8_t NO_TAPE_PIN = 4;
static constexpr uint8_t NO_TAPE_PIN_MASK = _BV(NO_TAPE_PIN);
static constexpr uint8_t LOW_TAPE_PIN = 5;
static constexpr uint8_t LOW_TAPE_PIN_MASK = _BV(LOW_TAPE_PIN);

void TPC::TPSensorsDriver::init() {
  PORT->DIRCLR = NO_TAPE_PIN_MASK | LOW_TAPE_PIN_MASK;
}

bool TPC::TPSensorsDriver::readNoTapeSensor() {
  return PORT->IN & NO_TAPE_PIN_MASK;
}

bool TPC::TPSensorsDriver::readLowTapeSensor() {
  return PORT->IN & LOW_TAPE_PIN_MASK;
}
