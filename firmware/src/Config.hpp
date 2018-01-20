#include "IO/Pin.hpp"
#include "IO/Port.hpp"

namespace Config {
  static const IO::Port codeSolenoidPort = IO::Port::A;
  static const IO::Pin feedSolenoidPin = { .port = IO::Port::B, .index = 0 };
}
