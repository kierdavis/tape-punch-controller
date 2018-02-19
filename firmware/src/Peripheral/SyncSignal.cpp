#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include "Peripheral/SyncSignal.hpp"
#include "Peripheral/SyncTimer.hpp"

static volatile PORT_t * const PORT = &PORTE;
static uint8_t constexpr PIN = 2;
static uint8_t constexpr PIN_MASK = _BV(PIN);

void Peripheral::SyncSignal::init() {
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
  Peripheral::SyncTimer::Hooks::sync_ID();
}
