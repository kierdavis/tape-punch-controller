#include <avr/interrupt.h>
#include <util/delay.h>

#include "TPC/Application.hpp"
#include "TPC/Log.hpp"
#include "TPC/MicrocontrollerDriver.hpp"
#include "TPC/TPController.hpp"
#include "TPC/USBDriver.hpp"

int main() {
  // First stage init.
  TPC::MicrocontrollerDriver::init();
  TPC::Log::init();
  LOG("[main] initialising...");

  // Second stage init.
  TPC::USBDriver::init();
  TPC::TPController::init();
  TPC::Application::init();
  sei();
  LOG("[main] ready");

  while (1) {
    TPC::USBDriver::tick();
    TPC::TPController::tick_IE();
    TPC::Application::tick_IE();
    _delay_us(1000);
  }
}
