#include <avr/interrupt.h>

#include "TapePunch.hpp"

static uint8_t test_data[] = {
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00010,
  0b00100,
  0b01000,
};

int main() {
  TapePunch::init();
  TapePunch::setDataSource(test_data, sizeof(test_data)/sizeof(test_data[0]));

  sei();
  while (1) {}
}
