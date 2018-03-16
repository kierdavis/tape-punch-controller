#include <stdbool.h>
#include <stdint.h>

#include "TPC/Config.hpp"
#include "TPC/Timekeeping.hpp"
#include "TPC/TimekeepingDriver.hpp"

using namespace TPC::Timekeeping;

TPC::Timekeeping::Interval::Interval(int16_t _ticks) : ticks(_ticks) {}

Interval TPC::Timekeeping::Interval::fromSeconds(int16_t seconds) {
  return Interval(((uint32_t) seconds) * TPC::Config::TICK_FREQUENCY);
}

Interval TPC::Timekeeping::Interval::fromMilliseconds(int16_t milliseconds) {
  return Interval((((uint32_t) milliseconds) * TPC::Config::TICK_FREQUENCY) / 1000);
}

TPC::Timekeeping::Timestamp::Timestamp(int16_t _ticks) : ticks(_ticks) {}

Timestamp TPC::Timekeeping::Timestamp::now() {
  return Timestamp(TPC::TimekeepingDriver::getCount());
}

bool TPC::Timekeeping::Timestamp::isBefore(Timestamp other) const {
  return until(other).ticks > 0;
}

bool TPC::Timekeeping::Timestamp::isAfter(Timestamp other) const {
  return since(other).ticks > 0;
}

Interval TPC::Timekeeping::Timestamp::since(Timestamp other) const {
  return Interval(ticks - other.ticks);
}

Interval TPC::Timekeeping::Timestamp::until(Timestamp other) const {
  return Interval(other.ticks - ticks);
}

Timestamp TPC::Timekeeping::Timestamp::add(Interval offset) const {
  return Timestamp(ticks + offset.ticks);
}

Timestamp TPC::Timekeeping::Timestamp::subtract(Interval offset) const {
  return Timestamp(ticks - offset.ticks);
}

void TPC::Timekeeping::init() {
  TPC::TimekeepingDriver::init();
}
