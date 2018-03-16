#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "TPC/LCDDriver.hpp"

enum class RS : uint8_t {
  CTRL, DATA
};

static volatile PORT_t * const DATA_PORT = &PORTC;
static constexpr uint8_t DATA_LSB_INDEX = 0;

static volatile PORT_t * const CTRL_PORT = &PORTB;
static constexpr uint8_t RS_INDEX = 6;
static constexpr uint8_t RS_MASK = _BV(RS_INDEX);
static constexpr uint8_t E_INDEX = 7;
static constexpr uint8_t E_MASK = _BV(E_INDEX);

static void configurePins() {
  DATA_PORT->DIRSET = 0xF << DATA_LSB_INDEX;
  DATA_PORT->OUTCLR = 0xF << DATA_LSB_INDEX;
  CTRL_PORT->DIRSET = RS_MASK | E_MASK;
  CTRL_PORT->OUTCLR = RS_MASK | E_MASK;
}

static void setData(uint8_t data) {
  DATA_PORT->OUTCLR = 0xF << DATA_LSB_INDEX;
  DATA_PORT->OUTSET = (data & 0xF) << DATA_LSB_INDEX;
}

static void setRS(RS rs) {
  volatile uint8_t * reg = (rs == RS::DATA) ? &CTRL_PORT->OUTSET
                                            : &CTRL_PORT->OUTCLR;
  *reg = RS_MASK;
}

static void setE(bool e) {
  volatile uint8_t * reg = e ? &CTRL_PORT->OUTSET
                             : &CTRL_PORT->OUTCLR;
  *reg = E_MASK;
}

static void pulseClock() {
  _delay_us(1);
  setE(true);
  _delay_us(1);
  setE(false);
}

static void write4(RS rs, uint8_t data) {
  setRS(rs);
  setData(data);
  pulseClock();
}

static void write8(RS rs, uint8_t data) {
  setRS(rs);
  setData(data >> 4);
  pulseClock();
  setData(data);
  pulseClock();
}

static void clearDisplay() {
  static constexpr uint8_t CMD = 0x01;
  write8(RS::CTRL, CMD);
  _delay_us(1600);
}

/*
static void returnHome() {
  static constexpr uint8_t CMD = 0x02;
  write8(RS::CTRL, CMD);
  _delay_us(1600);
}
*/

static constexpr uint8_t ENTRY_MODE_DECREMENT = 0 << 1;
static constexpr uint8_t ENTRY_MODE_INCREMENT = 1 << 1;
static constexpr uint8_t ENTRY_MODE_SHIFT = 1 << 0;
static void setEntryMode(const uint8_t params) {
  static constexpr uint8_t CMD = 0x04;
  write8(RS::CTRL, CMD | (params & 0x03));
  _delay_us(50);
}

static constexpr uint8_t DISPLAY_MODE_ENABLE_DISPLAY = 1 << 2;
static constexpr uint8_t DISPLAY_MODE_ENABLE_CURSOR = 1 << 1;
static constexpr uint8_t DISPLAY_MODE_ENABLE_BLINK = 1 << 0;
static void setDisplayMode(const uint8_t params) {
  static constexpr uint8_t CMD = 0x08;
  write8(RS::CTRL, CMD | (params & 0x07));
  _delay_us(50);
}

/*
static constexpr uint8_t SHIFT_CURSOR = 0 << 3;
static constexpr uint8_t SHIFT_DISPLAY = 1 << 3;
static constexpr uint8_t SHIFT_LEFT = 0 << 2;
static constexpr uint8_t SHIFT_RIGHT = 1 << 2;
static void shift(const uint8_t params) {
  static constexpr uint8_t CMD = 0x10;
  write8(RS::CTRL, CMD | (params & 0x0C));
  _delay_us(50);
}
*/

static constexpr uint8_t FUNCTION_4BIT = 0 << 4;
static constexpr uint8_t FUNCTION_8BIT = 1 << 4;
static constexpr uint8_t FUNCTION_1LINE = 0 << 3;
static constexpr uint8_t FUNCTION_2LINE = 1 << 3;
static constexpr uint8_t FUNCTION_5X8FONT = 0 << 2;
static constexpr uint8_t FUNCTION_5X10FONT = 1 << 2;
static void setFunction(const uint8_t params) {
  static constexpr uint8_t CMD = 0x20;
  write8(RS::CTRL, CMD | (params & 0x1C));
  _delay_us(50);
}

/*
static void setCGRAMAddr(const uint8_t addr) {
  static constexpr uint8_t CMD = 0x40;
  write8(RS::CTRL, CMD | (addr & 0x3F));
  _delay_us(50);
}
*/

static void setDDRAMAddr(const uint8_t addr) {
  static constexpr uint8_t CMD = 0x80;
  write8(RS::CTRL, CMD | (addr & 0x7F));
  _delay_us(50);
}

static void setCursorPos(const uint8_t row, const uint8_t col) {
  uint8_t addr = col;
  switch (row) {
    case 0: {
      addr += 0x00;
      break;
    }
    case 1: {
      addr += 0x40;
      break;
    }
    default: {
      // Invalid row.
      return;
    }
  }
  setDDRAMAddr(addr);
}

static void writeData(const uint8_t data) {
  write8(RS::DATA, data);
  _delay_us(50);
}

void TPC::LCDDriver::init() {
  configurePins();

  // Set bus to 4-bit mode.
  write4(RS::CTRL, 0x2);
  _delay_us(50);

  // Ensure display is off while we reconfigure.
  setDisplayMode(0);

  // Specify how many lines of text and which font to use.
  setFunction(FUNCTION_4BIT | FUNCTION_2LINE | FUNCTION_5X8FONT);

  // Set up entry mode so that the RAM address counter increments after each
  // byte is written.
  setEntryMode(ENTRY_MODE_INCREMENT);

  // Clear all text from the display.
  clearDisplay();

  // Turn the display on.
  setDisplayMode(DISPLAY_MODE_ENABLE_DISPLAY);
}

void TPC::LCDDriver::clear() {
  clearDisplay();
}

void TPC::LCDDriver::writeAt(const uint8_t row, const uint8_t col, const char * str) {
  setCursorPos(row, col);
  while (1) {
    char c = *str;
    if (c == '\0') { break; }
    writeData(c);
    str++;
  }
}

void TPC::LCDDriver::writeAtP(const uint8_t row, const uint8_t col, PGM_P str) {
  setCursorPos(row, col);
  while (1) {
    char c = pgm_read_byte(str);
    if (c == '\0') { break; }
    writeData(c);
    str++;
  }
}
