#include <stdbool.h>
#include <stdint.h>
#include <util/atomic.h>

#include "Config.hpp"
#include "Controller/TapePunch.hpp"
#include "TPC/TPJobManager.hpp"
#include "TPC/TPMotorDriver.hpp"
#include "TPC/TPSolenoidsDriver.hpp"
#include "TPC/TPSyncDriver.hpp"
#include "TPC/TPTimerDriver.hpp"

static volatile bool on = false;
static volatile uint16_t waitCount = 0;

void Controller::TapePunch::init() {
  // Initialise our peripherals.
  TPC::TPSolenoidsDriver::init();
  TPC::TPSyncDriver::init();
  TPC::TPTimerDriver::init();
  TPC::TPMotorDriver::init();
}

static void switchOn_IE() {
  TPC::TPMotorDriver::on();
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    // Interrupts disabled.
    on = true;
    waitCount = Config::STARTUP_CYCLES;
  }
}

static void switchOff_ID() {
  TPC::TPMotorDriver::off();
  on = false;
}

void Controller::TapePunch::setJob_IE(uint16_t length, const uint8_t * buffer) {
  TPC::TPJobManager::setJob_IE(length, buffer);
  bool on_;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    on_ = on;
  }
  if (!on_) {
    switchOn_IE();
  }
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
  TPC::TPJobManager::NextByteResult result = TPC::TPJobManager::nextByte_ID();
  if (result.hasByte) {
    TPC::TPSolenoidsDriver::energise(result.byte);
  } else {
    switchOff_ID();
  }
}

void Controller::TapePunch::Hooks::deenergiseSolenoids_ID() {
  TPC::TPSolenoidsDriver::deenergise();
}
