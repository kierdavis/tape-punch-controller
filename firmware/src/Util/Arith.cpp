#include <stdint.h>

#include "Util/Arith.hpp"

uint8_t Util::Arith::min(const uint8_t a, const uint8_t b) {
  return (a < b) ? a : b;
}

uint16_t Util::Arith::min(const uint16_t a, const uint16_t b) {
  return (a < b) ? a : b;
}
