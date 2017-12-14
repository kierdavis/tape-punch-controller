#ifndef __CONFIG_HPP
#define __CONFIG_HPP

#include "IO.hpp"

namespace Config {
  extern const IO::Port &codeSolenoidPort;
  extern const IO::Pin feedSolenoidPin;
  extern const IO::ExternalInterruptPin feedbackPin;
}

#endif // #ifndef __CONFIG_HPP
