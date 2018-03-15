#include <avr/interrupt.h>
#include <util/delay.h>

#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"
#include "TPC/MicrocontrollerDriver.hpp"
#include "TPC/TPController.hpp"
#include "TPC/UI.hpp"
#include "TPC/USBDriver.hpp"

int main() {
  // First stage init.
  TPC::MicrocontrollerDriver::init();
  TPC::Log::init();
  LOG("[main] initialising...");

  // Second stage init.
  TPC::Filesystem::init();
  TPC::USBDriver::init();
  TPC::TPController::init();
  TPC::UI::init();
  sei();
  LOG("[main] ready");

  while (1) {
    TPC::USBDriver::tick();
    TPC::TPController::tick_IE();
    TPC::UI::tick_IE();
    _delay_us(1000);
  }
}
