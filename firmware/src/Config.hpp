#include "IO/Pin.hpp"
#include "IO/Port.hpp"

namespace Config {
  static const IO::Port codeSolenoidPort =
  #if PLATFORM == DEV_IL_MATTO
    IO::Port::A;
  #else
    #error "invalid or unsupported PLATFORM"
  #endif

  static const IO::Pin feedSolenoidPin =
  #if PLATFORM == DEV_IL_MATTO
    { .port = IO::Port::B, .index = 0 };
  #else
    #error "invalid or unsupported PLATFORM"
  #endif
}
