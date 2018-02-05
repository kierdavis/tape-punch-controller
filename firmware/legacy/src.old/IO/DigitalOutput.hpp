#ifndef __TPC_IO_DIGITAL_OUTPUT_HPP
#define __TPC_IO_DIGITAL_OUTPUT_HPP

#include <stdbool.h>
#include <stdint.h>

#include "IO/Pin.hpp"
#include "IO/Port.hpp"

namespace IO {
  namespace DigitalOutput {
    void init(IO::Pin pin, bool initialValue = false);
    void set(IO::Pin pin, bool value);

    void init(IO::Port port, uint8_t initialValue = 0);
    void set(IO::Port port, uint8_t value);
  }
}

#endif
