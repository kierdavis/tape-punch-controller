#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "Controller/TapePunch.hpp"
#include "Peripheral/Serial.hpp"

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
  // First stage init.
  Peripheral::Serial::init();

  // Second stage init.
  Controller::TapePunch::init();

  // Done.
  static const char readyStr[] PROGMEM = "Ready.\r\n";
  Peripheral::Serial::writeStringP(readyStr);
  sei();

  Controller::TapePunch::addJob_IE(100); // leader (100 blank rows)
  Controller::TapePunch::addJob_IE(sizeof(DATA)/sizeof(DATA[0]), DATA);
  Controller::TapePunch::addJob_IE(200); // trailer (200 blank rows)

  while (1) {
    Controller::TapePunch::tick_IE();
    _delay_ms(20);
  }
}
