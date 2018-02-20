#include <stdbool.h>
#include <stdint.h>

#include <util/atomic.h>

#include "TPC/Config.hpp"
#include "TPC/Log.hpp"
#include "TPC/TPBodyBuffer.hpp"
#include "TPC/TPCoding.hpp"
#include "TPC/TPJobManager.hpp"
#include "TPC/Util.hpp"

enum class State : uint8_t {
  IDLE,
  LEADER,
  BODY,
  TRAILER,
};

static volatile State state = State::IDLE;
static volatile uint16_t count = 0;

static const uint8_t * bodyPtr = nullptr;
static uint16_t bodyCount = 0;
static bool inComment = false;

static void goToIdle_ID() {
  state = State::IDLE;
}

static void goToLeader_ID() {
  state = State::LEADER;
  count = TPC::Config::LEADER_LENGTH;
}

static void goToBody_ID() {
  state = State::BODY;
}

static void goToTrailer_ID() {
  state = State::TRAILER;
  count = TPC::Config::TRAILER_LENGTH;
}

static void refillBodyBuffer_IE() {
  bool bufferNotFull;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    bufferNotFull = !TPC::TPBodyBuffer::full_ID();
  }

  while (bufferNotFull && bodyCount != 0) {
    const uint8_t asciiChar = *bodyPtr;
    bodyPtr++;
    bodyCount--;

    const uint8_t tapeCode = TPC::TPCoding::asciiToEdsac(asciiChar);
    switch (tapeCode) {
      case TPC::TPCoding::UNPRINTABLE: {
        // Do nothing.
        break;
      }
      case TPC::TPCoding::BEGIN_COMMENT: {
        inComment = true;
        break;
      }
      case TPC::TPCoding::END_COMMENT: {
        inComment = false;
        break;
      }
      default: {
        if (!inComment) {
          ATOMIC_BLOCK(ATOMIC_FORCEON) {
            TPC::TPBodyBuffer::push_ID(tapeCode);
            bufferNotFull = !TPC::TPBodyBuffer::full_ID();
          }
        }
        break;
      }
    }
  }
}

void TPC::TPJobManager::setJob_IE(uint16_t count, const uint8_t * ptr) {
  bodyPtr = ptr;
  bodyCount = count;
  refillBodyBuffer_IE();
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    goToLeader_ID();
  }
  LOG("[TPJobManager] job added or changed");
}

void TPC::TPJobManager::tick_IE() {
  refillBodyBuffer_IE();
}

TPC::Util::MaybeUint8 TPC::TPJobManager::nextByte_ID() {
  switch (state) {
    case State::IDLE: {
      return TPC::Util::MaybeUint8(false);
    }
    case State::LEADER: {
      const uint16_t countMinusOne = count - 1;
      if (countMinusOne == 0) {
        goToBody_ID();
      } else {
        count = countMinusOne;
      }
      return TPC::Util::MaybeUint8(true, 0);
    }
    case State::BODY: {
      TPC::Util::MaybeUint8 result = TPC::TPBodyBuffer::pop_ID();
      if (result.hasValue) {
        return result;
      }
      // We've reached the end of the body.
      goToTrailer_ID();
      // We have no body data to print, so fall through to the `State::TRAILER`
      // block.
    }
    case State::TRAILER: {
      const uint16_t countMinusOne = count - 1;
      if (countMinusOne == 0) {
        goToIdle_ID();
      } else {
        count = countMinusOne;
      }
      return TPC::Util::MaybeUint8(true, 0);
    }
  }
  // Should be unreachable.
  return TPC::Util::MaybeUint8(false);
}
