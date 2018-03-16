#include <stdint.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "TPC/Log.hpp"
#include "TPC/MicrocontrollerDriver.hpp"

// The production signature row has its own special address space, in which the
// production signature values begin at offset zero. This structure should only
// be accessed using `readProdSigByte`.
static const NVM_PROD_SIGNATURES_t * const prodSigs = (NVM_PROD_SIGNATURES_t *) 0;

// Read a byte from the production signature row. `ptr` should point into
// `prodSigs`.
static uint8_t readProdSigByte(const uint8_t * ptr) {
  // Switch the behaviour of `pgm_read_byte` to use the production signature
  // address space rather than the program flash space (the default).
  NVM.CMD = NVM_CMD_READ_CALIB_ROW_gc;
  // Read the byte.
  const uint8_t val = pgm_read_byte(ptr);
  // Return the NVM controller to its default state.
  NVM.CMD = NVM_CMD_NO_OPERATION_gc;
  return val;
}

// Write `val` to the CCP-protected register pointed to by `ptr`. CCP stands
// for Configuration Change Protection, and is a special mechanism that must be
// used in order to modify certain critical hardware registers.
static void writeWithCCP(volatile uint8_t * ptr, uint8_t val) {
  // Write the magic incantation to the `CCP` register.
  CCP = CCP_IOREG_gc;
  // Perform the desired write operation within four clock cycles of the above.
  *ptr = val;
}

// Initialise the so-called "32 MHz" internal oscillator for 48 MHz operation.
static void init32MHzOscillator() {
  // Calibrate oscillator for 48MHz operation. An appropriate calibration
  // setting was determined during production test of the microcontroller, and
  // can be retrieved from the production signature row.
  // The cast to a `const uint8_t *` is necessary because `USBRCOSC` is marked
  // as `volatile` in the `NVM_PROD_SIGNATURES_t` structure despite it being
  // read-only. As a result, `&prodSigs->USBRCOSC` has the somewhat odd type
  // `const volatile uint8_t *`.
  DFLLRC32M.CALB = readProdSigByte((const uint8_t *) &prodSigs->USBRCOSC);
  // More magic calibration values.
  // Source: ATxmega C-series manual, section 4.15.19 (page 40).
  DFLLRC32M.COMP1 = 0x1B;
  DFLLRC32M.COMP2 = 0xB7;
  // Enable the oscillator.
  OSC.CTRL |= OSC_RC32MEN_bm;
  // Wait for it to be ready.
  while (!(OSC.STATUS & OSC_RC32MRDY_bm)) {}
}

// Perform the following steps to set up the microcontroller's clock system:
// - set the system clock source to the 32 MHz oscillator
// - set the CPU clock source to the system clock source with a divide-by-4
//   prescaler
// - set the USB peripheral clock source to the 32 MHz oscillator with no
//   prescaler
// - lock these settings until the next microcontroller reset.
// Assuming that the 32 MHz oscillator has been recalibrated for 48 MHz
// operation, this results in a USB peripheral clock frequency of 48 MHz and a
// CPU clock frequency of 12 MHz.
static void initClockSource() {
  // Configure prescalers that derive CPU clock from system clock.
  writeWithCCP(&CLK.PSCTRL, CLK_PSADIV_4_gc | CLK_PSBCDIV_1_1_gc);
  // Switch system clock source to the 32MHz oscillator.
  writeWithCCP(&CLK.CTRL, CLK_SCLKSEL_RC32M_gc);
  // Switch USB clock source to the 32MHZ oscillator.
  CLK.USBCTRL = CLK_USBPSDIV_1_gc | CLK_USBSRC_RC32M_gc | CLK_USBSEN_bm;
  // Lock the clock settings.
  writeWithCCP(&CLK.LOCK, CLK_LOCK_bm);
}

// Initialise the programmable interrupt controller by enabling all three
// priority levels of interrupts. Note that interrupts won't actually be
// enabled until `sei` is later called (in `main`).
static void initInterruptController() {
  writeWithCCP(&PMIC.CTRL, PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm);
}

// Initialise the microcontroller's internal subsystems.
void TPC::MicrocontrollerDriver::init() {
  init32MHzOscillator();
  initClockSource();
  initInterruptController();
  // TODO: watchdog timer
  // TODO: brownout detector
  // TODO: power management / sleep modes
}

void TPC::MicrocontrollerDriver::logResetSource() {
  uint8_t status = RST.STATUS;
  char statusStr[7] = {
    (status & RST_PORF_bm)  ? 'P' : '.',
    (status & RST_EXTRF_bm) ? 'X' : '.',
    (status & RST_BORF_bm)  ? 'B' : '.',
    (status & RST_WDRF_bm)  ? 'W' : '.',
    (status & RST_PDIRF_bm) ? 'F' : '.',
    (status & RST_SRF_bm)   ? 'S' : '.',
    '\0'
  };
  LOG("[MicrocontrollerDriver] reset source(s): ", (const char *) statusStr);
  // Clear all reset flags.
  RST.STATUS = RST_PORF_bm | RST_EXTRF_bm | RST_BORF_bm
             | RST_WDRF_bm | RST_PDIRF_bm | RST_SRF_bm;
}
