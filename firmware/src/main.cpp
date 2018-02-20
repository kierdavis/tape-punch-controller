#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "TPC/Log.hpp"
#include "TPC/MicrocontrollerDriver.hpp"
#include "TPC/TPController.hpp"
#include "TPC/Application.hpp"
#include "TPC/USBDriver.hpp"

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
  TPC::MicrocontrollerDriver::init();
  TPC::Log::init();
  LOG("[main] initialising...");

  // Second stage init.
  TPC::TPController::init();
  TPC::USBDriver::init();
  TPC::Application::init();
  sei();
  LOG("[main] ready");

  // Controller::TapePunch::addJob_IE(100); // leader (100 blank rows)
  // Controller::TapePunch::addJob_IE(sizeof(DATA)/sizeof(DATA[0]), DATA);
  // Controller::TapePunch::addJob_IE(200); // trailer (200 blank rows)

  while (1) {
    TPC::TPController::tick_IE();
    TPC::USBDriver::tick();
    _delay_us(1000);
  }
}
