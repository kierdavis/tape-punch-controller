// Hardware-specific configuration settings, such as pin numbers.

#ifndef __DEVICECONFIG_HPP
#define __DEVICECONFIG_HPP

#include <stdint.h>

#include "IO.hpp"

namespace Config {
  // The port to which the eight code solenoid drivers are attached.
  static const IO::Port &codeSolenoidPort =
    IO::Port::A;

  // The pin to which the feed solenoid driver is attached.
  static const IO::Pin feedSolenoidPin =
    { .port = IO::Port::B, .index = 0 };

  // The pin to which the enable (relay) driver is attached.
  static const IO::Pin enablePin =
    { .port = IO::Port::B, .index = 1 };

  // The clock prescaler used for the tape punch timer.
  // Valid choices are 1, 8, 64, 256 or 1024.
  static const uint16_t tapePunchTimerPrescaler = 1024;
}

#endif // #ifndef __DEVICECONFIG_HPP
