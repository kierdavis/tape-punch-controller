#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <stdint.h>

#include "Config.hpp"
#include "Peripheral/Serial.hpp"

static volatile USART_t * const USART = &USARTD0;
static volatile PORT_t * const PORT = &PORTD;
static uint8_t constexpr TXD_PIN = 3;
static uint8_t constexpr TXD_MASK = _BV(TXD_PIN);

static int8_t constexpr BSCALE = -5;

// 2**abs(BSCALE) cannot be more than half the minimum number of clock cycles of a frame.
// With 8-bit frames and each bit taking 16 cycles, this means 2**abs(BSCALE) <= 64.
// Hence abs(BSCALE) <= 6.
// See ATxmega C-series manual, section 21.9 "Fractional Baud Rate Generation".
static_assert(-6 <= BSCALE && BSCALE <= 6, "BSCALE must in range -6..6 inclusive");

static constexpr uint16_t calculateBSEL() {
  constexpr uint32_t f_per = (uint32_t) F_CPU;
  constexpr uint32_t f_baud = (uint32_t) Config::SERIAL_BAUD_RATE;
  if (BSCALE >= 0) {
    constexpr uint32_t pow_bscale = 1 << ((uint32_t) (BSCALE & 7));
    constexpr uint32_t bsel = f_per / (pow_bscale * 16 * f_baud) - 1;
    return (uint16_t) bsel;
  }
  else {
    constexpr uint32_t pow_bscale = 1 << ((uint32_t) ((-BSCALE) & 7));
    constexpr uint32_t bsel = (pow_bscale * f_per) / (16 * f_baud) - pow_bscale;
    return (uint16_t) bsel;
  }
}

static uint16_t constexpr BSEL = calculateBSEL();
static uint8_t constexpr BAUDCTRLA = (uint8_t) BSEL;
static uint8_t constexpr BAUDCTRLB = (((uint8_t) (BSCALE << 4)) & 0xF0)
                                   | (((uint8_t) (BSEL >> 8)) & 0x0F);

static void transmit(uint8_t data);

void Peripheral::Serial::init() {
  PORT->DIRSET = TXD_MASK;
  USART->CTRLA = USART_RXCINTLVL_OFF_gc | USART_TXCINTLVL_OFF_gc | USART_DREINTLVL_OFF_gc;
  USART->CTRLB = USART_TXEN_bm;
  USART->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
  USART->BAUDCTRLA = BAUDCTRLA;
  USART->BAUDCTRLB = BAUDCTRLB;

  SERIAL_WRITE("BSCALE 0x");
  Peripheral::Serial::writeHex4(BSCALE & 0xF);
  SERIAL_WRITE("\r\nBSEL 0x");
  Peripheral::Serial::writeHex16(BSEL);
  Peripheral::Serial::writeNewline();
}

void Peripheral::Serial::write(uint8_t data) {
  transmit(data);
}

void Peripheral::Serial::writeNewline() {
  Peripheral::Serial::write('\r');
  Peripheral::Serial::write('\n');
}

void Peripheral::Serial::writeStringP(PGM_P str) {
  while (1) {
    char c = pgm_read_byte(str);
    if (c == '\0') { break; }
    Peripheral::Serial::write((uint8_t) c);
    str++;
  }
}

void Peripheral::Serial::writeHex4(uint8_t val) {
  val &= 0xF;
  const char c = (val < 10) ? ('0' + val) : ('a' + val - 10);
  Peripheral::Serial::write(c);
}

void Peripheral::Serial::writeHex8(uint8_t val) {
  Peripheral::Serial::writeHex4(val >> 4);
  Peripheral::Serial::writeHex4(val);
}

void Peripheral::Serial::writeHex16(uint16_t val) {
  Peripheral::Serial::writeHex8(val >> 8);
  Peripheral::Serial::writeHex8(val);
}

static bool transmitBufferEmpty() {
  return USART->STATUS & USART_DREIF_bm;
}

static void transmit(uint8_t data) {
  while (!transmitBufferEmpty()) {}
  USART->DATA = data;
}
