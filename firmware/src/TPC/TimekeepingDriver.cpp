#include <stdint.h>

#include <avr/io.h>
#include <util/atomic.h>

#include "TPC/Config.hpp"
#include "TPC/TimekeepingDriver.hpp"

static void initTickTimer() {
  static constexpr uint32_t PRESCALER = 8;
  static constexpr uint32_t INCR_FREQUENCY = F_CPU / PRESCALER;
  static constexpr uint16_t INCRS_PER_TICK = INCR_FREQUENCY / TPC::Config::TICK_FREQUENCY;
  TCE0.CTRLA = TC_CLKSEL_OFF_gc;
  TCE0.CTRLB = TC_WGMODE_NORMAL_gc;
  TCE0.CTRLD = TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;
  TCE0.CTRLE = TC_BYTEM_NORMAL_gc;
  TCE0.INTCTRLA = TC_ERRINTLVL_OFF_gc | TC_OVFINTLVL_OFF_gc;
  TCE0.INTCTRLB = TC_CCDINTLVL_OFF_gc | TC_CCCINTLVL_OFF_gc
                | TC_CCBINTLVL_OFF_gc | TC_CCAINTLVL_OFF_gc;
  TCE0.CTRLFCLR = TC0_LUPD_bm | TC0_DIR_bm;
  TCE0.PER = INCRS_PER_TICK;
}

static void initEvent() {
  EVSYS.CH0MUX = EVSYS_CHMUX_TCE0_OVF_gc;
  EVSYS.CH0CTRL = EVSYS_DIGFILT_1SAMPLE_gc;
}

static void initCountTimer() {
  TCF0.CTRLA = TC_CLKSEL_OFF_gc;
  TCF0.CTRLB = TC_WGMODE_NORMAL_gc;
  TCF0.CTRLD = TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;
  TCF0.CTRLE = TC_BYTEM_NORMAL_gc;
  TCF0.INTCTRLA = TC_ERRINTLVL_OFF_gc | TC_OVFINTLVL_OFF_gc;
  TCF0.INTCTRLB = TC_CCDINTLVL_OFF_gc | TC_CCCINTLVL_OFF_gc
                | TC_CCBINTLVL_OFF_gc | TC_CCAINTLVL_OFF_gc;
  TCF0.CTRLFCLR = TC0_LUPD_bm | TC0_DIR_bm;
}

static void startTimers() {
  TCE0.CTRLA = TC_CLKSEL_DIV8_gc;
  TCF0.CTRLA = TC_CLKSEL_EVCH0_gc;
}

void TPC::TimekeepingDriver::init() {
  initTickTimer();
  initEvent();
  initCountTimer();
  startTimers();
}

int16_t TPC::TimekeepingDriver::getCount() {
  // Atomic read from TCF0.CNT.
  union {
    int16_t word;
    struct {
      uint8_t low;
      uint8_t high;
    } bytes;
  } u;
  u.bytes.low = TCF0.CNTL; // CNTH is copied into TEMP as a side effect.
  u.bytes.high = TCF0.CNTH;
  return u.word;
}
