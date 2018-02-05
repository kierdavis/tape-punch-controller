#include <stdbool.h>
#include <stdint.h>

#include "Config.hpp"
#include "IO/DigitalOutput.hpp"
#include "Peripheral/Solenoids.hpp"

void Peripheral::Solenoids::init() {
  IO::DigitalOutput::init(Config::CODE_SOLENOID_PORT);
  IO::DigitalOutput::init(Config::FEED_SOLENOID_PIN);
}

void Peripheral::Solenoids::energise(uint8_t codeValue) {
  IO::DigitalOutput::set(Config::CODE_SOLENOID_PORT, codeValue);
  IO::DigitalOutput::set(Config::FEED_SOLENOID_PIN, true);
}

void Peripheral::Solenoids::deenergise() {
  IO::DigitalOutput::set(Config::CODE_SOLENOID_PORT, 0);
  IO::DigitalOutput::set(Config::FEED_SOLENOID_PIN, false);
}
