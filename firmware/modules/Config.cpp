#include "Config.hpp"
#include "Port.hpp"

// The IO port to which the eight code solenoid drivers are attached. It is
// assumed they are attached in order (i.e. code solenoid N is wired to
// pin N on this port).
const Port &Config::codeSolenoidPort = Port::A;

// The IO pin to which the feed solenoid driver is attached.
const Pin Config::feedSolenoidPin = { .port = Port::B, .index = 0 };
