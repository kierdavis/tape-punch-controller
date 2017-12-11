#ifndef __TPC_PORT_HPP
#define __TPC_PORT_HPP

#include <stdint.h>

// Type Port represents one of the microcontroller's I/O ports. Since different
// microcontrollers have different numbers of, sizes of and interfaces to their
// I/O ports, this is heavily device-dependent.

#ifdef __AVR_ATmega644P__
  class Port {
  public:
    // The corresponding data direction (DDRx) register.
    volatile uint8_t *DDR;
    // The corresponding digital output (PORTx) register.
    volatile uint8_t *PORT;
    // The corresponding digital input (PINx) register.
    volatile uint8_t *PIN;

    // Declarations of constant Port instances for each of the microcontroller's
    // ports. The values of these member constants are defined in Port.cpp.
    static const Port A, B, C, D;
  };
#else
  #error "unsupported target device"
#endif

// Type Pin represents one of the pins on a microcontroller I/O port.
class Pin {
public:
  const Port &port;
  uint8_t index;
};

#endif // #ifndef __TPC_PORT_HPP
