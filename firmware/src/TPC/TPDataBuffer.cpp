#include <stdbool.h>
#include <stdint.h>

#include "TPC/Config.hpp"
#include "TPC/TPDataBuffer.hpp"
#include "TPC/Util.hpp"

using TPC::Config::DATA_BUFFER_SIZE;

static volatile uint8_t buffer[DATA_BUFFER_SIZE];
static volatile uint8_t pushIndex = 0;
static volatile uint8_t popIndex = 0;
static volatile uint8_t count = 0;

void TPC::TPDataBuffer::reset_ID() {
  pushIndex = 0;
  popIndex = 0;
  count = 0;
}

void TPC::TPDataBuffer::push_ID(const uint8_t value) {
  const uint8_t _count = count;
  if (_count < DATA_BUFFER_SIZE) {
    const uint8_t _pushIndex = pushIndex;
    buffer[_pushIndex] = value;
    pushIndex = (_pushIndex + 1) % DATA_BUFFER_SIZE;
    count = _count + 1;
  }
}

TPC::Util::MaybeUint8 TPC::TPDataBuffer::pop_ID() {
  const uint8_t _count = count;
  if (_count > 0) {
    const uint8_t _popIndex = popIndex;
    const uint8_t byte = buffer[_popIndex];
    popIndex = (_popIndex + 1) % DATA_BUFFER_SIZE;
    count = _count - 1;
    return TPC::Util::MaybeUint8(true, byte);
  } else {
    return TPC::Util::MaybeUint8(false);
  }
}

bool TPC::TPDataBuffer::full_ID() {
  return count >= DATA_BUFFER_SIZE;
}
