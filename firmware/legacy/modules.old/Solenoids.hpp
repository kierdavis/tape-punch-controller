// The Solenoids component encapsulates the behaviour of the tape punch's
// solenoids (electromagnets).

#ifndef __SOLENOIDS_HPP
#define __SOLENOIDS_HPP

#include <stdint.h>

namespace Solenoids {
  // Initialise the microcontroller pins that drive the solenoids.
  void init();

  // Energise the eight code solenoids according to the given bit pattern, and
  // energise the feed solenoiod unconditionally.
  void energise(uint8_t pattern);

  // De-energise all solenoids.
  void deenergise();
}

#endif // #ifndef __SOLENOIDS_HPP
