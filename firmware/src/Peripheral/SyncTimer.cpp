#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#include "Config.hpp"
#include "Controller/TapePunch.hpp"
#include "Peripheral/SyncTimer.hpp"

static void configureTimer();
static void setRunning(bool running);
static void clearCount();

void Peripheral::SyncTimer::init() {
  configureTimer();
}

void Peripheral::SyncTimer::stop() {
  Controller::TapePunch::Hooks::deenergiseSolenoids_ID();
  setRunning(false);
}

void Peripheral::SyncTimer::Hooks::sync_ID() {
  // TODO: check that timer count has the expected value (shaft rotation period
  // divided by timer tick period) and raise an error if not.
  // Reset the counter and start the timer (if it isn't already running).
  clearCount();
  setRunning(true);
}

static void energise_ID() {
  Controller::TapePunch::Hooks::energiseSolenoids_ID();
}

static void deenergise_ID() {
  Controller::TapePunch::Hooks::deenergiseSolenoids_ID();
}

static void overflow_ID() {
  // TODO: flag an error
  Controller::TapePunch::Hooks::deenergiseSolenoids_ID();
  setRunning(false);

}

// Platform-specific code is below.

#if defined(PLATFORM_IL_MATTO)
  static uint16_t constexpr PRESCALER = 1024;
  static uint8_t constexpr CLKSEL = _BV(CS02) | _BV(CS00);

  static double constexpr TICK_FREQ = ((double) F_CPU) / ((double) PRESCALER);
  static double constexpr TICK_PERIOD = 1.0 / TICK_FREQ;
  static double constexpr ENERGISE_COUNT_F = (Config::ENERGISE_DELAY / TICK_PERIOD) + 0.5;
  static double constexpr DEENERGISE_COUNT_F = (Config::DEENERGISE_DELAY / TICK_PERIOD) + 0.5;

  // Check ENERGISE_COUNT_F and DEENERGISE_COUNT_F have reasonable values before
  // we convert them to uint8_t.
  static_assert(ENERGISE_COUNT_F < 256,
    "ENERGISE_COUNT overflows its datatype (consider increasing PRESCALER)");
  static_assert(DEENERGISE_COUNT_F < 256,
    "DEENERGISE_COUNT overflows its datatype (consider increasing PRESCALER)");
  static_assert(ENERGISE_COUNT_F >= 16,
    "ENERGISE_COUNT is very small and may result in imprecise "
    "tape punch timing (consider decreasing PRESCALER)");
  static_assert(DEENERGISE_COUNT_F >= 16,
    "DEENERGISE_COUNT is very small and may result in imprecise "
    "tape punch timing (consider decreasing PRESCALER)");

  static uint8_t constexpr ENERGISE_COUNT = (uint8_t) ENERGISE_COUNT_F;
  static uint8_t constexpr DEENERGISE_COUNT = (uint8_t) DEENERGISE_COUNT_F;

  static void configureTimer() {
    // WGM0 = 000 (normal mode)
    // COM0A = 00 (OC0A output pin disabled)
    // COM1A = 00 (OC1A output pin disabled)
    // TOIE0 = 1 (interrupt on timer overflow)
    // OCIE0A = 1 (interrupt on compare match A)
    // OCIE0B = 1 (interrupt on compare match B)
    // Timer is initially not running.
    setRunning(false); // Sets TCCR0B and ensures timer is disabled.
    TCCR0A = 0;
    TIMSK0 = _BV(OCIE0B) | _BV(OCIE0A) | _BV(TOIE0);
    OCR0A = ENERGISE_COUNT;
    OCR0B = DEENERGISE_COUNT;
  }

  static void setRunning(bool running) {
    // WGM0 = 000 (normal mode)
    // When enabled, CS0 = CLKSEL
    // When disabled, CS0 = 0
    TCCR0B = running ? CLKSEL : 0;
  }

  static void clearCount() {
    TCNT0 = 0;
  }

  ISR(TIMER0_COMPA_vect) {
    energise_ID();
  }

  ISR(TIMER0_COMPB_vect) {
    deenergise_ID();
  }

  ISR(TIMER0_OVF_vect) {
    overflow_ID();
  }

#elif defined(PLATFORM_PCB)
  static uint16_t constexpr PRESCALER = 4;
  static uint8_t constexpr CLKSEL = TC_CLKSEL_DIV4_gc;

  static double constexpr TICK_FREQ = ((double) F_CPU) / ((double) PRESCALER);
  static double constexpr TICK_PERIOD = 1.0 / TICK_FREQ;
  static double constexpr ENERGISE_COUNT_F = (Config::ENERGISE_DELAY / TICK_PERIOD) + 0.5;
  static double constexpr DEENERGISE_COUNT_F = (Config::DEENERGISE_DELAY / TICK_PERIOD) + 0.5;

  // Check ENERGISE_COUNT_F and DEENERGISE_COUNT_F have reasonable values before we convert them to uint8_t.
  static_assert(ENERGISE_COUNT_F < 65536,
    "ENERGISE_COUNT overflows its datatype (consider increasing PRESCALER)");
  static_assert(DEENERGISE_COUNT_F < 65536,
    "DEENERGISE_COUNT overflows its datastype (consider increasing PRESCALER)");
  static_assert(ENERGISE_COUNT_F >= 256,
    "ENERGISE_COUNT is very small and may result in imprecise"
    "tape punch timing (consider decreasing PRESCALER)");
  static_assert(DEENERGISE_COUNT_F >= 256,
    "DEENERGISE_COUNT is very small and may result in imprecise"
    "tape punch timing (consider decreasing PRESCALER)");

  static uint16_t constexpr ENERGISE_COUNT = (uint16_t) ENERGISE_COUNT_F;
  static uint16_t constexpr DEENERGISE_COUNT = (uint16_t) DEENERGISE_COUNT_F;

  static void configureTimer() {
    setRunning(false); // Sets CTRLA and ensures timer is disabled.
    // CCxEN = 0 (all output compare pins disabled)
    // WGMODE = NORMAL
    TCC0.CTRLB = TC_WGMODE_NORMAL_gc;
    // EVACT = OFF (no event bus interaction)
    // EVDLY = 0 (no event bus interaction)
    // EVSEL = OFF (no event bus interaction)
    TCC0.CTRLD = TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;
    // BYTEM = NORMAL (single 16-bit counter)
    TCC0.CTRLE = TC_BYTEM_NORMAL_gc;
    // ERRINTLVL = OFF (no error interrupt)
    // OVFINTLVL = MED (medium priority overflow interrupt)
    TCC0.INTCTRLA = TC_ERRINTLVL_OFF_gc | TC_OVFINTLVL_MED_gc;
    // CCDINTLVL = OFF (no compare match D interrupt)
    // CCCINTLVL = OFF (no compare match C interrupt)
    // CCBINTLVL = OFF (high priority compare match B interrupt)
    // CCAINTLVL = OFF (high priority compare match A interrupt)
    TCC0.INTCTRLB = TC_CCDINTLVL_OFF_gc | TC_CCCINTLVL_OFF_gc |
                    TC_CCBINTLVL_HI_gc | TC_CCAINTLVL_HI_gc;
    // LUPD = 0 (updating is unlocked)
    // DIR = 0 (count upwards)
    TCC0.CTRLFCLR = TC0_LUPD_bm | TC0_DIR_bm;
    // Period and compare match levels.
    TCC0.PER = 0xFFFF;
    TCC0.CCA = ENERGISE_COUNT;
    TCC0.CCB = DEENERGISE_COUNT;
  }

  static void setRunning(bool running) {
    // When enabled, CTRLA = CLKSEL.
    // When disabled, CTRLA = OFF.
    TCC0.CTRLA = running ? CLKSEL : TC_CLKSEL_OFF_gc;
  }

  static void clearCount() {
    TCC0.CNT = 0;
  }

  ISR(TCC0_CCA_vect) {
    energise_ID();
  }

  ISR(TCC0_CCB_vect) {
    deenergise_ID();
  }

  ISR(TCC0_OVF_vect) {
    overflow_ID();
  }

#else
  #error "invalid or unsupported PLATFORM"
#endif
