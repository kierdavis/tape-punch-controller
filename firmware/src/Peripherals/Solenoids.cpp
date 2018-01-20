#include <stdbool.h>
#include <stdint.h>

#include "Config.hpp"
#include "IO/DigitalOutput.hpp"
#include "Peripherals/Solenoids.hpp"

void Peripherals::Solenoids::init() {
  IO::DigitalOutput::init(Config::codeSolenoidPort);
  IO::DigitalOutput::init(Config::feedSolenoidPin);
}

void Peripherals::Solenoids::energise(uint8_t codeValue) {
  IO::DigitalOutput::set(Config::codeSolenoidPort, codeValue);
  IO::DigitalOutput::set(Config::feedSolenoidPin, true);
}

void Peripherals::Solenoids::deenergise() {
  IO::DigitalOutput::set(Config::codeSolenoidPort, 0);
  IO::DigitalOutput::set(Config::feedSolenoidPin, false);
}
