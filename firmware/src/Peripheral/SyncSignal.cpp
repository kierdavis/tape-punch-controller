#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include "Peripheral/SyncSignal.hpp"
#include "Peripheral/SyncTimer.hpp"

static void configureInterrupt();

void Peripheral::SyncSignal::init() {
  configureInterrupt();
}

static void handleInterrupt_ID() {
  Peripheral::SyncTimer::Hooks::sync_ID();
}

// Platform-specific code is below.

#if defined(PLATFORM_IL_MATTO)
  static void configureInterrupt() {
    // Rising edge of INT2 generates an interrupt request.
    EICRA |= _BV(ISC21) | _BV(ISC20);
    // Enable interrupt handler.
    EIMSK |= _BV(INT2);
  }

  ISR(INT2_vect) {
    handleInterrupt_ID();
  }

#elif defined(PLATFORM_PCB)
  static volatile PORT_t * const PORT = &PORTE;
  static uint8_t constexpr PIN = 2;
  static uint8_t constexpr PIN_MASK = _BV(PIN);

  static void configureInterrupt() {
    volatile uint8_t * const pinctrls = &PORT->PIN0CTRL;
    // Configure pin as an input.
    PORT->DIRCLR = PIN_MASK;
    // Attach pin to interrupt 0.
    PORT->INT0MASK |= PIN_MASK;
    // Set edge detection mode on this pin to rising edge.
    pinctrls[PIN] = PORT_ISC_RISING_gc;
    // Enable interrupt 0 (high priority).
    PORT->INTCTRL |= PORT_INT0LVL_HI_gc;
  }

  ISR(PORTE_INT0_vect) {
    handleInterrupt_ID();
  }

#else
  #error "invalid or unsupported PLATFORM"
#endif
