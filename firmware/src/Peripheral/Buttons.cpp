#include <stdbool.h>
#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#include "Peripheral/Buttons.hpp"
#include "Peripheral/Serial.hpp"

enum class State : uint8_t {
  NONE_PRESSED,
  CONFIRM_PRESSED,
  CANCEL_PRESSED,
  BOTH_PRESSED,
  AFTER_BOTH_PRESSED,
};

static void configurePins();
static bool readConfirm();
static bool readCancel();

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

static void onConfirm_ID() {
  SERIAL_WRITE("[Buttons] confirm\r\n");
}

static void onCancel_ID() {
  SERIAL_WRITE("[Buttons] cancel\r\n");
}

static void onBoth_ID() {
  SERIAL_WRITE("[Buttons] confirm+cancel\r\n");
}

static void update_ID() {
  static State savedState = State::NONE_PRESSED;

  const State oldState = savedState;
  State newState = readState();

  if (oldState == State::CONFIRM_PRESSED && newState == State::NONE_PRESSED) {
    onConfirm_ID();
  } else if (oldState == State::CANCEL_PRESSED && newState == State::NONE_PRESSED) {
    onCancel_ID();
  } else if (oldState == State::BOTH_PRESSED && newState != State::BOTH_PRESSED) {
    onBoth_ID();
    newState = State::AFTER_BOTH_PRESSED;
  }

  savedState = newState;
}

void Peripheral::Buttons::init() {
  configurePins();
}

// Platform-specific code is below.

#if defined(PLATFORM_PCB)
  static volatile PORT_t * const PORT = &PORTA;
  static uint8_t constexpr CONFIRM_PIN = 2;
  static uint8_t constexpr CONFIRM_PIN_MASK = _BV(CONFIRM_PIN);
  static uint8_t constexpr CANCEL_PIN = 1;
  static uint8_t constexpr CANCEL_PIN_MASK = _BV(CANCEL_PIN);

  static void configurePins() {
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

  ISR(PORTA_INT0_vect) {
    update_ID();
  }

#else
  #error "invalid or unsupported PLATFORM"
#endif
