#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>

#include "DigitalOutput.hpp"
#include "Port.hpp"

#ifdef __AVR_ATmega644P__

  void DigitalOutput::initPin(const Pin &pin) {
    *pin.port.DDR |= _BV(pin.index);
  }
  void DigitalOutput::setPin(const Pin &pin, bool state) {
    if (state) {
      *pin.port.PORT |= _BV(pin.index);
    } else {
      *pin.port.PORT &= ~_BV(pin.index);
    }
  }
  void DigitalOutput::initPort(const Port &port) {
    *port.DDR = 0xFF;
  }
  void DigitalOutput::setPort(const Port &port, uint8_t state) {
    *port.PORT = state;
  }

#else
  #error "unsupported target device"
#endif
