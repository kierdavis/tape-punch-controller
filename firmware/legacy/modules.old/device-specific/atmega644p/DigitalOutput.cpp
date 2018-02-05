#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>

#include "DigitalOutput.hpp"
#include "IO.hpp"

void DigitalOutput::initPin(const IO::Pin &pin) {
  *pin.port.DDR |= _BV(pin.index);
}

void DigitalOutput::setPin(const IO::Pin &pin, bool state) {
  if (state) {
    *pin.port.PORT |= _BV(pin.index);
  }
  else {
    *pin.port.PORT &= ~_BV(pin.index);
  }
}

void DigitalOutput::initPort(const IO::Port &port) {
  *port.DDR = 0xFF;
}

void DigitalOutput::setPort(const IO::Port &port, uint8_t state) {
  *port.PORT = state;
}
