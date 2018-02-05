#include <stdbool.h>
#include <stdint.h>

#include "Controller/TapePunch.hpp"
#include "Peripheral/Motor.hpp"

static volatile bool isOn = false;
static volatile uint8_t startupCount = 0;

static void switchOn() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    isOn = true;
    startupCount = Config::startupCycles;
  }
  Peripheral::Motor::switchOn();
}

static void switchOff() {
  Peripheral::Motor::switchOff();
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    isOn = false;
  }
}

void Controller::TapePunch::init() {
  Peripheral::Solenoids::init();
  Peripheral::Motor::init();
}

void Controller::TapePunch::Hooks::energiseSolenoids() {
  if (!isOn) {
    // Do nothing.
    return;
  }

  uint8_t startupCount_ = startupCount
  if (startupCount_ != 0) {
    // Currently waiting for the mechanism to reach a stable speed.
    startupCount = startupCount_ - 1;
    return;
  }

  Controller::TapePunchData::PullByteResult res;
  res = Controller::TapePunchData::pullByte();
  if (res.hasData) {
    Peripheral::Solenoids::energise(res.data);
  }
  else {
    switchOff();
  }
}

void Controller::TapePunch::Hooks::deenergiseSolenoids() {
  Peripheral::Solenoids::deenergise();
}
