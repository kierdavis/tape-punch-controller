#include <stdbool.h>
#include <avr/io.h>

#include "DigitalOutput.hpp"
#include "Port.hpp"

void DigitalOutput::init(const Pin &pin) {
  #ifdef __AVR_ATmega644P__
    *pin.port.DDR |= _BV(pin.index);
  #else
    #error "unsupported target device"
  #endif
}

void DigitalOutput::set(const Pin &pin, bool state) {
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
