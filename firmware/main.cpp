#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "TapePunch.hpp"

static volatile uint8_t test_data[] = {
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00010,
  0b00100,
  0b01000,
};

static volatile TapePunch::Job job4(TapePunch::Job::Type::BLANK, 160, nullptr);
static volatile TapePunch::Job job3(TapePunch::Job::Type::DATA,  160, test_data, &job4);
static volatile TapePunch::Job job2(TapePunch::Job::Type::BLANK, 160, nullptr,   &job3);
static volatile TapePunch::Job job1(TapePunch::Job::Type::NOP,   90,  nullptr,   &job2);

int main() {
  TapePunch::init();
  sei();

  TapePunch::setJobs(&job1);
  TapePunch::setEnabled(true);
  while (TapePunch::busy()) {
    _delay_ms(100);
  }
  TapePunch::setEnabled(false);
}
