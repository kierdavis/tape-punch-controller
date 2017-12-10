#include <avr/io.h>

#include "Port.hpp"

#ifdef __AVR_ATmega644P__
  const Port Port::A = { .DDR = &DDRA, .PORT = &PORTA, .PIN = &PINA };
  const Port Port::B = { .DDR = &DDRB, .PORT = &PORTB, .PIN = &PINB };
  const Port Port::C = { .DDR = &DDRC, .PORT = &PORTC, .PIN = &PINC };
  const Port Port::D = { .DDR = &DDRD, .PORT = &PORTD, .PIN = &PIND };
#else
  #error "unsupported target device"
#endif
