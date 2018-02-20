#include <stdbool.h>
#include <stdint.h>

#include <util/atomic.h>

#include "Config.hpp"
#include "TPC/TPJobManager.hpp"

using TPC::TPJobManager::NextByteResult;

enum class State : uint8_t {
  IDLE,
  LEADER,
  BODY,
  TRAILER,
};

// TODO: use the FAT

static volatile State state = State::IDLE;
static volatile uint16_t count = 0;
static const uint8_t * volatile bodyPtr = nullptr;
static volatile uint16_t bodyCount = 0;

static void goToIdle_ID() {
  state = State::IDLE;
}

static void goToLeader_ID() {
  state = State::LEADER;
  count = Config::LEADER_LENGTH;
}

static void goToBody_ID() {
  state = State::BODY;
}

static void goToTrailer_ID() {
  state = State::TRAILER;
  count = Config::TRAILER_LENGTH;
}

void TPC::TPJobManager::setJob_IE(uint16_t count, const uint8_t * ptr) {
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    bodyPtr = ptr;
    bodyCount = count;
    goToLeader_ID();
  }
}

NextByteResult TPC::TPJobManager::nextByte_ID() {
  switch (state) {
    case State::IDLE: {
      return NextByteResult(false);
    }
    case State::LEADER: {
      const uint16_t countMinusOne = count - 1;
      if (countMinusOne == 0) {
        goToBody_ID();
      } else {
        count = countMinusOne;
      }
      return NextByteResult(true, 0);
    }
    case State::BODY: {
      const uint8_t byte = *(bodyPtr++);
      const uint16_t countMinusOne = bodyCount - 1;
      if (countMinusOne == 0) {
        goToTrailer_ID();
      } else {
        bodyCount = countMinusOne;
      }
      return NextByteResult(true, byte);
    }
    case State::TRAILER: {
      const uint16_t countMinusOne = count - 1;
      if (countMinusOne == 0) {
        goToIdle_ID();
      } else {
        count = countMinusOne;
      }
      return NextByteResult(true, 0);
    }
  }
  // Should be unreachable.
  return NextByteResult(false);
}
