// The DigitalOutput component encapsulates the behaviour of the
// microcontroller's standard general-purpose digital outputs.

#ifndef __TPC_DIGITALOUTPUT_HPP
#define __TPC_DIGITALOUTPUT_HPP

#include <stdbool.h>

#include "Port.hpp"

namespace DigitalOutput {
  // Initialise a pin as a digital output.
  void init(const Pin &pin);

  // Set the state of a digital output (high or low).
  void set(const Pin &pin, bool state);
}

#endif // #ifndef __TPC_DIGITALOUTPUT_HPP
