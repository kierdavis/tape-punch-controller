#include <stdbool.h>
#include <stdint.h>

#include <util/atomic.h>

#include "TPC/Application.hpp"
#include "TPC/Config.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/Scheduler.hpp"
#include "TPC/Timekeeping.hpp"
#include "TPC/TPController.hpp"
#include "TPC/TPDataProvider.hpp"
#include "TPC/TPMotorDriver.hpp"
#include "TPC/TPSensorsDriver.hpp"
#include "TPC/TPSolenoidsDriver.hpp"
#include "TPC/TPSyncDriver.hpp"
#include "TPC/TPTimerDriver.hpp"
#include "TPC/Util.hpp"

static volatile uint16_t waitCount = 0;

static void scheduleTask() {
  TPC::Scheduler::schedule(
    TPC::Scheduler::TaskID::TP_CONTROLLER_SERVICE,
    TPC::Timekeeping::Interval::fromMilliseconds(50)
  );
}

static void cancelTask() {
  TPC::Scheduler::cancel(TPC::Scheduler::TaskID::TP_CONTROLLER_SERVICE);
}

void TPC::TPController::init() {
  // Initialise our peripherals.
  TPC::TPSolenoidsDriver::init();
  TPC::TPSyncDriver::init();
  TPC::TPTimerDriver::init();
  TPC::TPMotorDriver::init();
  TPC::TPSensorsDriver::init();
  TPC::TPDataProvider::init();
}

static bool isOn() {
  return TPC::TPMotorDriver::isOn();
}

static void switchOn() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    if (!isOn()) {
      TPC::TPMotorDriver::on();
      waitCount = TPC::Config::STARTUP_CYCLES;
    }
  }
  scheduleTask();
}

static void switchOff() {
  TPC::TPMotorDriver::off();
  cancelTask();
}

void TPC::TPController::setJob_IE(TPC::Filesystem::Reader reader, uint16_t length) {
  TPC::TPDataProvider::setJob_IE(reader, length);
  switchOn();
}

void TPC::TPController::clearJob_IE() {
  TPC::TPDataProvider::clearJob_IE();
  switchOff();
}

bool TPC::TPController::readNoTapeSensor() {
  return TPC::TPSensorsDriver::readNoTapeSensor();
}

bool TPC::TPController::readLowTapeSensor() {
  return TPC::TPSensorsDriver::readLowTapeSensor();
}

void TPC::TPController::Hooks::energiseSolenoids_ID() {
  if (!isOn()) {
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
    switchOff();
    TPC::Scheduler::schedule(TPC::Scheduler::TaskID::PRINTING_COMPLETE);
  }
}

void TPC::TPController::Hooks::deenergiseSolenoids_ID() {
  TPC::TPSolenoidsDriver::deenergise();
}

static void checkNoTapeSensor_IE() {
  static bool prevState = false;
  bool currState = TPC::TPController::readNoTapeSensor();
  if (!prevState && currState) {
    TPC::Application::warnNoTapeDuringPrint_IE();
  }
  prevState = currState;
}

static void checkLowTapeSensor_IE() {
  static bool prevState = false;
  bool currState = TPC::TPController::readLowTapeSensor();
  if (!prevState && currState) {
    TPC::Application::warnLowTapeDuringPrint_IE();
  }
  prevState = currState;
}

void TPC::TPController::serviceTask_IE() {
  if (isOn()) {
    checkNoTapeSensor_IE();
    checkLowTapeSensor_IE();
  }
  scheduleTask();
}
