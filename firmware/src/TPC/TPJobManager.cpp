#include <stdbool.h>
#include <stdint.h>

#include <util/atomic.h>

#include "Config.hpp"
#include "TPC/TPBodyBuffer.hpp"
#include "TPC/TPCoding.hpp"
#include "TPC/TPJobManager.hpp"
#include "Util/Maybe.hpp"

enum class State : uint8_t {
  IDLE,
  LEADER,
  BODY,
  TRAILER,
};

// TODO: use the FAT

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
  count = Config::LEADER_LENGTH;
}

static void goToBody_ID() {
  state = State::BODY;
}

static void goToTrailer_ID() {
  state = State::TRAILER;
  count = Config::TRAILER_LENGTH;
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
}

void TPC::TPJobManager::tick_IE() {
  refillBodyBuffer_IE();
}

Util::Maybe::Uint8 TPC::TPJobManager::nextByte_ID() {
  switch (state) {
    case State::IDLE: {
      return Util::Maybe::Uint8(false);
    }
    case State::LEADER: {
      const uint16_t countMinusOne = count - 1;
      if (countMinusOne == 0) {
        goToBody_ID();
      } else {
        count = countMinusOne;
      }
      return Util::Maybe::Uint8(true, 0);
    }
    case State::BODY: {
      Util::Maybe::Uint8 result = TPC::TPBodyBuffer::pop_ID();
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
      return Util::Maybe::Uint8(true, 0);
    }
  }
  // Should be unreachable.
  return Util::Maybe::Uint8(false);
}
