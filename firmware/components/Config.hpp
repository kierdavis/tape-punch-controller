#ifndef __TPC_CONFIG_HPP
#define __TPC_CONFIG_HPP

#include "Port.hpp"

namespace Config {
  // The IO port to which the eight code solenoid drivers are attached. It is
  // assumed they are attached in order (i.e. code solenoid N is wired to
  // pin N on this port).
  extern const Port &codeSolenoidPort;

  // The IO pin to which the feed solenoid driver is attached.
  extern const Pin feedSolenoidPin;
}

#endif // #ifndef __TPC_CONFIG_HPP
