#include <stdbool.h>
#include <stdint.h>

#include "Config.hpp"
#include "DigitalOutput.hpp"
#include "Solenoids.hpp"
#include "SolenoidTimer.hpp"

void Solenoids::init() {
  DigitalOutput::initPort(Config::codeSolenoidPort);
  DigitalOutput::initPin(Config::feedSolenoidPin);
}

void Solenoids::activate(uint8_t pattern) {
  DigitalOutput::setPort(Config::codeSolenoidPort, pattern);
  DigitalOutput::setPin(Config::feedSolenoidPin, true);
}

void Solenoids::deactivate() {
  DigitalOutput::setPort(Config::codeSolenoidPort, 0);
  DigitalOutput::setPin(Config::feedSolenoidPin, false);
}

void Solenoids::pulse(uint8_t pattern) {
  Solenoids::activate(pattern);
  SolenoidTimer::start();
}
