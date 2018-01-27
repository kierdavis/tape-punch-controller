#include <avr/interrupt.h>
#include <util/delay.h>

#include "Controller/TapePunch.hpp"

static uint8_t const DATA[] = {
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00010,
  0b00100,
  0b01000,
  0b10000,
};

int main() {
  Controller::TapePunch::init();
  sei();

  Controller::TapePunch::addJob_IE(100); // leader (100 blank rows)
  Controller::TapePunch::addJob_IE(sizeof(DATA)/sizeof(DATA[0]), DATA);
  Controller::TapePunch::addJob_IE(200); // trailer (200 blank rows)

  while (1) {
    Controller::TapePunch::tick_IE();
    _delay_ms(20);
  }
}
