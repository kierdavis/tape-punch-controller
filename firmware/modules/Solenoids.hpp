// The Solenoids component encapsulates the behaviour of the tape punch's
// solenoids (electromagnets).

#ifndef __TPC_SOLENOIDS_HPP
#define __TPC_SOLENOIDS_HPP

#include <stdint.h>

#include "Config.hpp"
#include "Port.hpp"

namespace Solenoids {
  // Initialise the microcontroller pins that drive the solenoids.
  void init();

  // Activate the eight code solenoids according to the given bit pattern, and
  // activate the feed solenoiod unconditionally.
  void activate(uint8_t pattern);

  // Deactivate all solenoids.
  void deactivate();
}

#endif // #ifndef __TPC_SOLENOIDS_HPP
