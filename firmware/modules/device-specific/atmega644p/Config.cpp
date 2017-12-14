#include <stdint.h>

#include "Config.hpp"
#include "IO.hpp"

const IO::Port &Config::codeSolenoidPort = IO::Port::A;
const IO::Pin Config::feedSolenoidPin =
  { .port = IO::Port::B, .index = 0 };
const IO::ExternalInterruptPin Config::feedbackPin =
  IO::ExternalInterruptPin::INT2_;

const float Config::solenoidDuration = 4.5e-3;
const uint16_t Config::solenoidTimerPrescaler = 256;
