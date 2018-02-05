// Non-hardware-specific configuration settings.

#ifndef __CONFIG_HPP
#define __CONFIG_HPP

#include "DeviceConfig.hpp"

namespace Config {
  // Tape punch drive shaft speed, in cycles per second.
  // With 60Hz mains input, this is 110 cycles per second.
  // With 50Hz mains input, this falls by the same ratio (5/6).
  static const double shaftFrequency = 110.0 * 5.0/6.0;

  // Angle of displacement (in degrees) of the tape punch shaft at which the
  // magnet embedded in the flywheel passes underneath the feedback coil. The
  // "zero degrees" position is when the punch pins are at their highest.
  static const double syncAngle = 180.0;

  // Angle of displacement (in degrees) of the tape punch shaft at which the
  // solenoids should be energised.
  static const double energiseAngle = 268.0;

  // Angle of displacement (in degrees) of the tape punch shaft at which the
  // solenoids should be de-energised.
  static const double deenergiseAngle = 56.0;
  // (above value found through trial and error, may need tweaking)
}

#include "DerivedConfig.hpp"

#endif // #ifndef __CONFIG_HPP
