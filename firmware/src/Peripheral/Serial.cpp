#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <stdint.h>

#include "Config.hpp"
#include "Peripheral/Serial.hpp"

static void initUART();
static void transmit(uint8_t data);

void Peripheral::Serial::init() {
  initUART();
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

// Platform-specific code is below.

#if defined(PLATFORM_IL_MATTO)
  static void initUART() {
    // U2X = 0 (don't double the transmission speed)
    // MPCM = 0 (don't use multi-processor communication mode)
    UCSR0A = 0;
    // RXCIE = 1 (interrupt on receive complete)
    // TXCIE = 0 (don't interrupt on transmission complete)
    // UDRIE = 0 (don't interrupt on transmit buffer empty)
    // RXEN = 1 (enable receiver)
    // TXEN = 1 (enable transmitter)
    // UCSZ = 011 (8-bit data)
    //UCSR0B = _BV(RXCIE0) | _BV(RXEN0) | _BV(TXEN0);
    UCSR0B = _BV(TXEN0);
    // UMSEL = 00 (asynchronous UART)
    // UPM = 00 (no parity)
    // USBS = 0 (one stop bit)
    // UCSZ = 011 (8-bit data)
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
    // Baud rate register.
    constexpr uint8_t UBRR0val = F_CPU / (16 * Config::SERIAL_BAUD_RATE) - 1;
    UBRR0 = UBRR0val;

    SERIAL_WRITE("UBRR0 0x");
    Peripheral::Serial::writeHex8(UBRR0val);
    Peripheral::Serial::writeNewline();
  }

  static bool transmitBufferEmpty() {
    return UCSR0A & _BV(UDRE0);
  }

  static void transmit(uint8_t data) {
    while (!transmitBufferEmpty()) {}
    UDR0 = data;
  }

#elif defined(PLATFORM_PCB)
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

  static void initUART() {
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

  static bool transmitBufferEmpty() {
    return USART->STATUS & USART_DREIF_bm;
  }

  static void transmit(uint8_t data) {
    while (!transmitBufferEmpty()) {}
    USART->DATA = data;
  }

#else
  #error "invalid or unsupported PLATFORM"
#endif
