#ifndef __DIGITALOUTPUT_HPP
#define __DIGITALOUTPUT_HPP

#include <stdbool.h>
#include <stdint.h>

#include "IO.hpp"

namespace DigitalOutput {
  void initPin(const IO::Pin &pin);
  void setPin(const IO::Pin &pin, bool state);
  void initPort(const IO::Port &port);
  void setPort(const IO::Port &port, uint8_t state);
}

#endif // #ifndef __DIGITALOUTPUT_HPP
