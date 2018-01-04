#ifndef __DERIVEDCONFIG_HPP
#define __DERIVEDCONFIG_HPP

#include <stdint.h>

static constexpr double normalise_angle(double x) {
  return (x < 0.0) ? (x + 360.0) :
         (x >= 360.0) ? (x - 360.0) : x;
}

namespace Config {
  // The frequency at which the tape punch timer's counter increments.
  static const double tapePunchTimerFreq =
    ((double) F_CPU) / ((double) tapePunchTimerPrescaler);

  // The time period between successive increments of the tape punch timer's
  // counter.
  static const double tapePunchTimerPeriod = 1.0 / tapePunchTimerFreq;

  // The period of rotation of tape punch drive shaft.
  static const double shaftPeriod = 1.0 / shaftFrequency;

  // The angle moved through by the shaft between the point at which the magnet
  // passes under the feedback coil and the point at which the solenoids are
  // energised/deenergised.
  static const double energiseAngleOffset =
    normalise_angle(energiseAngle - syncAngle);
  static const double deenergiseAngleOffset =
    normalise_angle(deenergiseAngle - syncAngle);

  // Like shaftEnergiseAngleOffset, but is the duration of time passed between
  // the two points rather the angle moved by the shaft.
  static const double energiseTimeOffset =
    (energiseAngleOffset / 360.0) * shaftPeriod;
  static const double deenergiseTimeOffset =
    (deenergiseAngleOffset / 360.0) * shaftPeriod;

  // The value of the tape punch timer's counter at the point at which the
  // solenoids should be energised/deenergised.
  static const uint8_t energiseCount =
    (uint8_t) (energiseTimeOffset / tapePunchTimerPeriod);
  static const uint8_t deenergiseCount =
    (uint8_t) (deenergiseTimeOffset / tapePunchTimerPeriod);
}

#endif // #ifndef __DERIVEDCONFIG_HPP
