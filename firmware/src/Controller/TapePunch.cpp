#include <stdbool.h>
#include <stdint.h>
#include <util/atomic.h>

#include "Config.hpp"
#include "Controller/JobQueue.hpp"
#include "Controller/TapePunch.hpp"
#include "Peripheral/Motor.hpp"
#include "Peripheral/SyncSignal.hpp"
#include "Peripheral/SyncTimer.hpp"
#include "TPC/TPSolenoidsDriver.hpp"

static volatile bool on = false;
static volatile uint16_t waitCount = 0;

void Controller::TapePunch::init() {
  // Initialise our peripherals.
  TPC::TPSolenoidsDriver::init();
  Peripheral::SyncSignal::init();
  Peripheral::SyncTimer::init();
  Peripheral::Motor::init();
}

static void switchOn_IE() {
  Peripheral::Motor::on();
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    // Interrupts disabled.
    on = true;
    waitCount = Config::STARTUP_CYCLES;
  }
}

static void switchOff_ID() {
  Peripheral::Motor::off();
  on = false;
}

void Controller::TapePunch::addJob_IE(uint16_t length, const uint8_t * buffer) {
  Controller::JobQueue::addJob_IE(length, buffer);
  bool on_;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    on_ = on;
  }
  if (!on_) {
    switchOn_IE();
  }
}

void Controller::TapePunch::tick_IE() {
  Controller::JobQueue::tick_IE();
}

void Controller::TapePunch::Hooks::energiseSolenoids_ID() {
  if (!on) {
    return;
  }
  uint16_t waitCount_ = waitCount;
  if (waitCount_ != 0) {
    waitCount = waitCount_ - 1;
    return;
  }
  Controller::JobQueue::PopByteResult result = Controller::JobQueue::popByte_ID();
  if (result.hasData) {
    TPC::TPSolenoidsDriver::energise(result.data);
  } else {
    switchOff_ID();
  }
}

void Controller::TapePunch::Hooks::deenergiseSolenoids_ID() {
  TPC::TPSolenoidsDriver::deenergise();
}
