#include <avr/interrupt.h>

#include "TapePunch.hpp"

int main() {
  TapePunch::init();

  sei();
  while (1) {}
}
