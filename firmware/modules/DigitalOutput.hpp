// The DigitalOutput component encapsulates the behaviour of the
// microcontroller's standard general-purpose digital outputs.

#ifndef __TPC_DIGITALOUTPUT_HPP
#define __TPC_DIGITALOUTPUT_HPP

#include <stdbool.h>
#include <stdint.h>

#include "Port.hpp"

namespace DigitalOutput {
  // Initialise a pin as a digital output.
  void initPin(const Pin &pin);

  // Set the state of a digital output (high or low).
  void setPin(const Pin &pin, bool state);

  // Initialise all pins on a port as digital outputs.
  void initPort(const Port &port);

  // Set the state of all pins on a port at once.
  void setPort(const Port &port, uint8_t state);
}

#endif // #ifndef __TPC_DIGITALOUTPUT_HPP
