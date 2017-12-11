#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>

#include "DigitalOutput.hpp"
#include "Port.hpp"

void DigitalOutput::initPin(const Pin &pin) {
  #ifdef __AVR_ATmega644P__
    *pin.port.DDR |= _BV(pin.index);
  #else
    #error "unsupported target device"
  #endif
}

void DigitalOutput::setPin(const Pin &pin, bool state) {
  #ifdef __AVR_ATmega644P__
    if (state) {
      *pin.port.PORT |= _BV(pin.index);
    } else {
      *pin.port.PORT &= ~_BV(pin.index);
    }
  #else
    #error "unsupported target device"
  #endif
}

void DigitalOutput::initPort(const Port &port) {
  #ifdef __AVR_ATmega644P__
    *port.DDR = 0xFF;
  #else
    #error "unsupported target device"
  #endif
}

void DigitalOutput::setPort(const Port &port, uint8_t state) {
  #ifdef __AVR_ATmega644P__
    *port.PORT = state;
  #else
    #error "unsupported target device"
  #endif
}
