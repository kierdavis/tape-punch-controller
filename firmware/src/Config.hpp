#include "IO/Pin.hpp"
#include "IO/Port.hpp"

namespace Config {
  static const IO::Port CODE_SOLENOID_PORT =
  #if PLATFORM == DEV_IL_MATTO
    IO::Port::A;
  #else
    #error "invalid or unsupported PLATFORM"
  #endif

  static const IO::Pin FEED_SOLENOID_PIN =
  #if PLATFORM == DEV_IL_MATTO
    { .port = IO::Port::B, .index = 0 };
  #else
    #error "invalid or unsupported PLATFORM"
  #endif
}
