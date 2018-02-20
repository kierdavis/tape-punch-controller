#include <stdbool.h>
#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#include "TPC/Config.hpp"
#include "TPC/Log.hpp"
#include "TPC/TPController.hpp"
#include "TPC/TPTimerDriver.hpp"

static uint16_t constexpr PRESCALER = 4;
static uint8_t constexpr CLKSEL = TC_CLKSEL_DIV4_gc;

static double constexpr TICK_FREQ = ((double) F_CPU) / ((double) PRESCALER);
static double constexpr TICK_PERIOD = 1.0 / TICK_FREQ;
static double constexpr ENERGISE_COUNT_F = (TPC::Config::ENERGISE_DELAY / TICK_PERIOD) + 0.5;
static double constexpr DEENERGISE_COUNT_F = (TPC::Config::DEENERGISE_DELAY / TICK_PERIOD) + 0.5;

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

static void setRunning(bool running) {
  // When enabled, CTRLA = CLKSEL.
  // When disabled, CTRLA = OFF.
  TCC0.CTRLA = running ? CLKSEL : TC_CLKSEL_OFF_gc;
}

static void clearCount() {
  TCC0.CNT = 0;
}

void TPC::TPTimerDriver::init() {
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

  LOG("[TPTimerDriver] ENERGISE_COUNT = 0x", ENERGISE_COUNT);
  LOG("[TPTimerDriver] DEENERGISE_COUNT = 0x", DEENERGISE_COUNT);
}

void TPC::TPTimerDriver::stop() {
  TPC::TPController::Hooks::deenergiseSolenoids_ID();
  setRunning(false);
}

void TPC::TPTimerDriver::Hooks::sync_ID() {
  // TODO: check that timer count has the expected value (shaft rotation period
  // divided by timer tick period) and raise an error if not.
  // Reset the counter and start the timer (if it isn't already running).
  clearCount();
  setRunning(true);
}

ISR(TCC0_CCA_vect) {
  TPC::TPController::Hooks::energiseSolenoids_ID();
}

ISR(TCC0_CCB_vect) {
  TPC::TPController::Hooks::deenergiseSolenoids_ID();
}

ISR(TCC0_OVF_vect) {
  // TODO: flag an error
  TPC::TPController::Hooks::deenergiseSolenoids_ID();
  setRunning(false);
}
