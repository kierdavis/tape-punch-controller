#ifndef __TPC_MICROCONTROLLER_DRIVER_HPP
#define __TPC_MICROCONTROLLER_DRIVER_HPP

namespace TPC {
  namespace MicrocontrollerDriver {
    // Initialise the microcontroller's internal subsystems.
    void init();

    void logResetSource();
  }
}

#endif
