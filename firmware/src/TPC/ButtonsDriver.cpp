#include <stdbool.h>
#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#include "TPC/ButtonsDriver.hpp"
#include "TPC/Scheduler.hpp"
#include "TPC/UI.hpp"

enum class State : uint8_t {
  NONE_PRESSED,
  CONFIRM_PRESSED,
  CANCEL_PRESSED,
  BOTH_PRESSED,
  AFTER_BOTH_PRESSED,
};

static volatile PORT_t * const PORT = &PORTA;
static uint8_t constexpr CONFIRM_PIN = 2;
static uint8_t constexpr CONFIRM_PIN_MASK = _BV(CONFIRM_PIN);
static uint8_t constexpr CANCEL_PIN = 1;
static uint8_t constexpr CANCEL_PIN_MASK = _BV(CANCEL_PIN);

void TPC::ButtonsDriver::init() {
  volatile uint8_t * const pinctrls = &PORT->PIN0CTRL;
  // Configure pins as inputs.
  PORT->DIRCLR = CONFIRM_PIN_MASK | CANCEL_PIN_MASK;
  // Attach pins to interrupt 0.
  PORT->INT0MASK |= CONFIRM_PIN_MASK | CANCEL_PIN_MASK;
  // Set edge detection mode on these pins to both edges.
  pinctrls[CONFIRM_PIN] = PORT_ISC_BOTHEDGES_gc;
  pinctrls[CANCEL_PIN] = PORT_ISC_BOTHEDGES_gc;
  // Enable interrupt 0 (low priority).
  PORT->INTCTRL |= PORT_INT0LVL_LO_gc;
}

static bool readConfirm() {
  return !(PORT->IN & CONFIRM_PIN_MASK);
}

static bool readCancel() {
  return !(PORT->IN & CANCEL_PIN_MASK);
}

static State readState() {
  if (readConfirm()) {
    if (readCancel()) {
      return State::BOTH_PRESSED;
    } else {
      return State::CONFIRM_PRESSED;
    }
  } else {
    if (readCancel()) {
      return State::CANCEL_PRESSED;
    } else {
      return State::NONE_PRESSED;
    }
  }
}

ISR(PORTA_INT0_vect) {
  static State savedState = State::NONE_PRESSED;

  const State oldState = savedState;
  State newState = readState();

  if (oldState == State::CONFIRM_PRESSED && newState == State::NONE_PRESSED) {
    TPC::Scheduler::schedule(TPC::Scheduler::TaskID::UI_CONFIRM_BUTTON);
  } else if (oldState == State::CANCEL_PRESSED && newState == State::NONE_PRESSED) {
    TPC::Scheduler::schedule(TPC::Scheduler::TaskID::UI_CANCEL_BUTTON);
  } else if (oldState == State::BOTH_PRESSED && newState != State::BOTH_PRESSED) {
    TPC::Scheduler::schedule(TPC::Scheduler::TaskID::UI_BOTH_BUTTONS);
    if (newState == State::CONFIRM_PRESSED || newState == State::CANCEL_PRESSED) {
      // Move to the pseudo-state AFTER_BOTH_PRESSED instead of
      // CONFIRM_PRESSED/CANCEL_PRESSED, so that we don't trigger another
      // button event when the second button is later released.
      newState = State::AFTER_BOTH_PRESSED;
    }
  }

  savedState = newState;
}
