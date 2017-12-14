#ifndef __CONFIG_HPP
#define __CONFIG_HPP

#include <stdint.h>

#include "IO.hpp"

namespace Config {
  extern const IO::Port &codeSolenoidPort;
  extern const IO::Pin feedSolenoidPin;
  extern const IO::ExternalInterruptPin feedbackPin;

  extern const float solenoidDuration;
  extern const uint16_t solenoidTimerPrescaler;
}

#endif // #ifndef __CONFIG_HPP
