#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>

#include "IO/DigitalOutput.hpp"

static volatile uint8_t * directionReg(IO::Port port) {
  switch (port) {
    #if PLATFORM == IL_MATTO
      case IO::Port::A: { return &DDRA; }
      case IO::Port::B: { return &DDRB; }
      case IO::Port::C: { return &DDRC; }
      case IO::Port::D: { return &DDRD; }
      default:          { return nullptr; }
    #else
      #error "invalid or unsupported PLATFORM"
    #endif
  }
}

static volatile uint8_t * dataReg(IO::Port port) {
  switch (port) {
    #if PLATFORM == IL_MATTO
      case IO::Port::A: { return &PORTA; }
      case IO::Port::B: { return &PORTB; }
      case IO::Port::C: { return &PORTC; }
      case IO::Port::D: { return &PORTD; }
      default:          { return nullptr; }
    #else
      #error "invalid or unsupported PLATFORM"
    #endif
  }
}

void IO::DigitalOutput::init(IO::Pin pin, bool initialValue) {
  uint8_t mask = 1 << pin.index;
  *directionReg(pin.port) |= mask;
  IO::DigitalOutput::set(pin, initialValue);
}

void IO::DigitalOutput::set(IO::Pin pin, bool value) {
  uint8_t mask = 1 << pin.index;
  if (value) {
    *dataReg(pin.port) |= mask;
  }
  else {
    *dataReg(pin.port) &= ~mask;
  }
}

void IO::DigitalOutput::init(IO::Port port, uint8_t initialValue) {
  *directionReg(port) = 0xFF;
  IO::DigitalOutput::set(port, initialValue);
}

void IO::DigitalOutput::set(IO::Port port, uint8_t value) {
  *dataReg(port) = value;
}
