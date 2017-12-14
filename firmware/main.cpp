#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "FeedbackSignal.hpp"
#include "Hooks.hpp"
#include "Solenoids.hpp"
#include "SolenoidTimer.hpp"

// static uint8_t body = 200;
// static uint8_t pos = 0;
// static const uint8_t sequence[] PROGMEM = {
//   0b00001,
//   0b00010,
//   0b00100,
//   0b01000,
//   0b10000,
//   0b01000,
//   0b00100,
//   0b00010,
// };
// static bool moreDataBytes() {
//   return body > 0;
// }
// static uint8_t nextDataByte() {
//   uint8_t value = 0;
//   if (body > 0) {
//     value = pgm_read_byte(&sequence[pos]);
//     pos = (pos + 1) % 8;
//     body--;
//   }
//   return value;
// }

static uint8_t pos = 0;
static const uint8_t data[] PROGMEM = {
  0x1f,
  0x02,
  0x04,
  0x02,
  0x1f,
  0x00,
  0x00,
  0x1f,
  0x15,
  0x11,
  0x00,
  0x00,
  0x1f,
  0x05,
  0x1a,
  0x00,
  0x00,
  0x1f,
  0x05,
  0x1a,
  0x00,
  0x00,
  0x03,
  0x1c,
  0x03,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x11,
  0x0a,
  0x04,
  0x0a,
  0x11,
  0x00,
  0x00,
  0x1f,
  0x02,
  0x04,
  0x02,
  0x1f,
  0x00,
  0x00,
  0x1e,
  0x05,
  0x1e,
  0x00,
  0x00,
  0x12,
  0x15,
  0x09,
  0x00,
  0x00,
};
static bool moreDataBytes() {
  return pos < (sizeof(data)/sizeof(data[0]));
}
static uint8_t nextDataByte() {
  return pgm_read_byte(&data[pos++]);
}

static uint8_t wait = 200;
static uint8_t lead_in = 0;
static uint8_t lead_out = 70;
static uint8_t skip = 0;

void Hooks::onFeedbackPulse() {
  skip = (skip + 1) % 2;
  if (skip < 1) return;
  _delay_us(250);
  uint8_t value = 0x00;
  if (wait > 0) {
    wait--;
    return;
  }
  else if (lead_in > 0) {
    lead_in--;
  }
  else if (moreDataBytes()) {
    value = nextDataByte();
  }
  else if (lead_out > 0) {
    lead_out--;
  }
  else {
    return;
  }
  Solenoids::pulse(value);
}

// static uint8_t wait = 200;
// static uint8_t lead_in = 15;
// static uint8_t lead_out = 50;
// static uint8_t pos = 0;


// void Hooks::onFeedbackPulse() {
//   uint8_t value = 0x00;
//   if (wait > 0) {
//     wait--;
//     return;
//   }
//   else if (lead_in > 0) {
//     lead_in--;
//   }
//   else if (pos < sizeof(data)/sizeof(data[0])) {
//     value = pgm_read_byte(&data[pos]);
//     pos++;
//   }
//   else if (lead_out > 0) {
//     lead_out--;
//   }
//   else {
//     return;
//   }
//   Solenoids::pulse(value);
// }

int main() {
  Solenoids::init();
  SolenoidTimer::init();
  FeedbackSignal::init();

  sei();
  while (1) {}
}
