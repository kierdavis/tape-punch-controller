#include <stdbool.h>
#include <stdint.h>

#include <util/atomic.h>

#include "TPC/Config.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/TPController.hpp"
#include "TPC/TPDataProvider.hpp"
#include "TPC/TPMotorDriver.hpp"
#include "TPC/TPSensorsDriver.hpp"
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
  TPC::TPSensorsDriver::init();
  TPC::TPDataProvider::init();
}

static void switchOn_IE() {
  TPC::TPMotorDriver::on();
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    // Interrupts disabled.
    on = true;
    waitCount = TPC::Config::STARTUP_CYCLES;
  }
}

static void switchOff_ID() {
  TPC::TPMotorDriver::off();
  on = false;
}

static void switchOff_IE() {
  TPC::TPMotorDriver::off();
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    on = false;
  }
}

bool TPC::TPController::isOn_IE() {
  bool on_;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    on_ = on;
  }
  return on_;
}

void TPC::TPController::setJob_IE(TPC::Filesystem::Reader reader, uint16_t length) {
  TPC::TPDataProvider::setJob_IE(reader, length);
  if (!isOn_IE()) {
    switchOn_IE();
  }
}

void TPC::TPController::clearJob_IE() {
  TPC::TPDataProvider::clearJob_IE();
  switchOff_IE();
}

bool TPC::TPController::readNoTapeSensor() {
  return TPC::TPSensorsDriver::readNoTapeSensor();
}

bool TPC::TPController::readLowTapeSensor() {
  return TPC::TPSensorsDriver::readLowTapeSensor();
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
  TPC::Util::MaybeUint8 result = TPC::TPDataProvider::nextByte_ID();
  if (result.hasValue) {
    TPC::TPSolenoidsDriver::energise(result.value);
  } else {
    switchOff_ID();
  }
}

void TPC::TPController::Hooks::deenergiseSolenoids_ID() {
  TPC::TPSolenoidsDriver::deenergise();
}
