#include <avr/io.h>

#include "IO.hpp"

const IO::Port IO::Port::A = { .DDR = &DDRA, .PORT = &PORTA, .PIN = &PINA };
const IO::Port IO::Port::B = { .DDR = &DDRB, .PORT = &PORTB, .PIN = &PINB };
const IO::Port IO::Port::C = { .DDR = &DDRC, .PORT = &PORTC, .PIN = &PINC };
const IO::Port IO::Port::D = { .DDR = &DDRD, .PORT = &PORTD, .PIN = &PIND };
