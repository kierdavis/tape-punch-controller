// Hardware-specific configuration settings, such as pin numbers.

#ifndef __DEVICECONFIG_HPP
#define __DEVICECONFIG_HPP

#include "IO.hpp"

namespace Config {
  // The port to which the eight code solenoid drivers are attached.
  static const IO::Port &codeSolenoidPort =
    IO::Port::A;

  // The pin to which the feed solenoid driver is attached.
  static const IO::Pin feedSolenoidPin =
    { .port = IO::Port::B, .index = 0 };
}

#endif // #ifndef __DEVICECONFIG_HPP
