#include <avr/interrupt.h>
#include <util/delay.h>

#include "TPC/Application.hpp"
#include "TPC/Log.hpp"
#include "TPC/MicrocontrollerDriver.hpp"
#include "TPC/Scheduler.hpp"

int main() {
  // First stage init.
  TPC::MicrocontrollerDriver::init();
  TPC::Log::init();
  LOG(INFO, "[main] initialising...");

  // Second stage init.
  TPC::MicrocontrollerDriver::logResetSource();
  TPC::Scheduler::init();
  TPC::Application::init();
  sei();
  LOG(IMPORTANT, "[main] ready");

  while (1) {
    TPC::Scheduler::serviceTasks();
  }
}
