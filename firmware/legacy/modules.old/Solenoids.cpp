#include <stdbool.h>
#include <stdint.h>

#include "Config.hpp"
#include "DigitalOutput.hpp"
#include "Solenoids.hpp"

void Solenoids::init() {
  DigitalOutput::initPort(Config::codeSolenoidPort);
  DigitalOutput::setPort(Config::codeSolenoidPort, 0);
  DigitalOutput::initPin(Config::feedSolenoidPin);
  DigitalOutput::setPin(Config::feedSolenoidPin, false);
}

void Solenoids::energise(uint8_t pattern) {
  DigitalOutput::setPort(Config::codeSolenoidPort, pattern);
  DigitalOutput::setPin(Config::feedSolenoidPin, true);
}

void Solenoids::deenergise() {
  DigitalOutput::setPort(Config::codeSolenoidPort, 0);
  DigitalOutput::setPin(Config::feedSolenoidPin, false);
}
