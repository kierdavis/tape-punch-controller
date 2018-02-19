#ifndef __TPC_CONFIG_HPP
#define __TPC_CONFIG_HPP

#include <avr/io.h>

static constexpr double normaliseAngle(double x) {
  return (x < 0.0) ? (x + 360.0) :
         (x >= 360.0) ? (x - 360.0) : x;
}

namespace Config {
  static double constexpr SHAFT_FREQUENCY = 110.0 * 5.0/6.0;
  static double constexpr SHAFT_PERIOD = 1.0 / SHAFT_FREQUENCY;

  static double constexpr SYNC_ANGLE = 180.0;

  static double constexpr ENERGISE_ANGLE = 268.0;
  static double constexpr ENERGISE_REL_ANGLE = normaliseAngle(ENERGISE_ANGLE - SYNC_ANGLE);
  static double constexpr ENERGISE_DELAY = (ENERGISE_REL_ANGLE / 360.0) * SHAFT_PERIOD;

  static double constexpr DEENERGISE_ANGLE = 56.0;
  static double constexpr DEENERGISE_REL_ANGLE = normaliseAngle(DEENERGISE_ANGLE - SYNC_ANGLE);
  static double constexpr DEENERGISE_DELAY = (DEENERGISE_REL_ANGLE / 360.0) * SHAFT_PERIOD;

  static uint16_t constexpr STARTUP_CYCLES = 92;

  static uint32_t constexpr SERIAL_BAUD_RATE = 115200;

  static uint16_t constexpr USB_VENDOR_ID = 0x03EB; // Atmel
  static uint16_t constexpr USB_PRODUCT_ID = 0x2040; // LUFA test PID (must change this before shipping to customer)

  static uint8_t constexpr MAX_NUM_FILES = 16;
}

#endif
