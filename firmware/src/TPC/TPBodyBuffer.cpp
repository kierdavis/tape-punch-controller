#include <stdbool.h>
#include <stdint.h>

#include "Config.hpp"
#include "TPC/TPBodyBuffer.hpp"
#include "Util/Maybe.hpp"

using Config::BODY_BUFFER_SIZE;

static volatile uint8_t buffer[BODY_BUFFER_SIZE];
static volatile uint8_t pushIndex = 0;
static volatile uint8_t popIndex = 0;
static volatile uint8_t count = 0;

void TPC::TPBodyBuffer::push_ID(const uint8_t value) {
  const uint8_t _count = count;
  if (_count < BODY_BUFFER_SIZE) {
    const uint8_t _pushIndex = pushIndex;
    buffer[_pushIndex] = value;
    pushIndex = (_pushIndex + 1) % BODY_BUFFER_SIZE;
    count = _count + 1;
  }
}

Util::Maybe::Uint8 TPC::TPBodyBuffer::pop_ID() {
  const uint8_t _count = count;
  if (_count > 0) {
    const uint8_t _popIndex = popIndex;
    const uint8_t byte = buffer[_popIndex];
    popIndex = (_popIndex + 1) % BODY_BUFFER_SIZE;
    count = _count - 1;
    return Util::Maybe::Uint8(true, byte);
  } else {
    return Util::Maybe::Uint8(false);
  }
}

bool TPC::TPBodyBuffer::full_ID() {
  return count >= BODY_BUFFER_SIZE;
}
