#include <stdint.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "Platform.hpp"

// Production signature row has its own address space.
static const volatile NVM_PROD_SIGNATURES_t * const prodSigs = (NVM_PROD_SIGNATURES_t *) 0;

static uint8_t readProdSigByte(const volatile uint8_t * ptr) {
  NVM.CMD = NVM_CMD_READ_CALIB_ROW_gc;
  const uint8_t val = pgm_read_byte(ptr);
  NVM.CMD = NVM_CMD_NO_OPERATION_gc;
  return val;
}

static void writeWithCCP(volatile uint8_t * ptr, uint8_t val) {
  CCP = CCP_IOREG_gc;
  *ptr = val;
}

static void init32MHzOscillator() {
  // Calibrate oscillator for 48MHz operation.
  DFLLRC32M.CALB = readProdSigByte(&prodSigs->USBRCOSC);
  DFLLRC32M.COMP1 = 0x1B;
  DFLLRC32M.COMP2 = 0xB7;
  // Enable oscillator and wait for it to be ready.
  OSC.CTRL |= OSC_RC32MEN_bm;
  while (!(OSC.STATUS & OSC_RC32MRDY_bm)) {}
}

static void initSystemClock() {
  init32MHzOscillator();
  // Configure system clock prescalers.
  writeWithCCP(&CLK.PSCTRL, CLK_PSADIV_4_gc | CLK_PSBCDIV_1_1_gc);
  // Switch system clock source to the 32MHz oscillator.
  // With the /4 prescaler in effect, the system clock frequency is 12 MHz.
  writeWithCCP(&CLK.CTRL, CLK_SCLKSEL_RC32M_gc);
  // Switch USB clock source to the 32MHZ oscillator.
  CLK.USBCTRL = CLK_USBPSDIV_1_gc | CLK_USBSRC_RC32M_gc | CLK_USBSEN_bm;
  // Lock the clock settings until the next reset.
  writeWithCCP(&CLK.LOCK, CLK_LOCK_bm);
}

static void initInterruptController() {
  writeWithCCP(&PMIC.CTRL, PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm);
}

void Platform::init() {
  initSystemClock();
  initInterruptController();
}
