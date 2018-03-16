#include <avr/interrupt.h>
#include <util/delay.h>

#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"
#include "TPC/MicrocontrollerDriver.hpp"
#include "TPC/Scheduler.hpp"
#include "TPC/TPController.hpp"
#include "TPC/UI.hpp"
#include "TPC/USBDriver.hpp"

int main() {
  // First stage init.
  TPC::MicrocontrollerDriver::init();
  TPC::Log::init();
  LOG("[main] initialising...");

  // Second stage init.
  TPC::MicrocontrollerDriver::logResetSource();
  TPC::Scheduler::init();
  TPC::Filesystem::init();
  TPC::USBDriver::init();
  TPC::TPController::init();
  TPC::UI::init();
  sei();
  LOG("[main] ready");

  while (1) {
    TPC::Scheduler::serviceTasks();
  }
}
