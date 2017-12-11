// The Solenoids component encapsulates the behaviour of the tape punch's
// solenoids (electromagnets).

#ifndef __SOLENOIDS_HPP
#define __SOLENOIDS_HPP

#include <stdint.h>

namespace Solenoids {
  // Initialise the microcontroller pins that drive the solenoids.
  void init();

  // Activate the eight code solenoids according to the given bit pattern, and
  // activate the feed solenoiod unconditionally.
  void activate(uint8_t pattern);

  // Deactivate all solenoids.
  void deactivate();
}

#endif // #ifndef __SOLENOIDS_HPP
