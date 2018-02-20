#include <stdbool.h>
#include <stdint.h>
#include <util/atomic.h>

#include "Config.hpp"
#include "TPC/TPController.hpp"
#include "TPC/TPJobManager.hpp"
#include "TPC/TPMotorDriver.hpp"
#include "TPC/TPSolenoidsDriver.hpp"
#include "TPC/TPSyncDriver.hpp"
#include "TPC/TPTimerDriver.hpp"
#include "TPC/Util.hpp"

static volatile bool on = false;
static volatile uint16_t waitCount = 0;

void TPC::TPController::init() {
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

void TPC::TPController::setJob_IE(uint16_t length, const uint8_t * buffer) {
  TPC::TPJobManager::setJob_IE(length, buffer);
  bool on_;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    on_ = on;
  }
  if (!on_) {
    switchOn_IE();
  }
}

void TPC::TPController::tick_IE() {
  TPC::TPJobManager::tick_IE();
}

void TPC::TPController::Hooks::energiseSolenoids_ID() {
  if (!on) {
    return;
  }
  uint16_t waitCount_ = waitCount;
  if (waitCount_ != 0) {
    waitCount = waitCount_ - 1;
    return;
  }
  TPC::Util::MaybeUint8 result = TPC::TPJobManager::nextByte_ID();
  if (result.hasValue) {
    TPC::TPSolenoidsDriver::energise(result.value);
  } else {
    switchOff_ID();
  }
}

void TPC::TPController::Hooks::deenergiseSolenoids_ID() {
  TPC::TPSolenoidsDriver::deenergise();
}
