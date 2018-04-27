#include <stdbool.h>
#include <stdint.h>

#include <util/atomic.h>

#include "TPC/Config.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"
#include "TPC/Scheduler.hpp"
#include "TPC/Timekeeping.hpp"
#include "TPC/TPDataBuffer.hpp"
#include "TPC/TPCoding.hpp"
#include "TPC/TPDataProvider.hpp"
#include "TPC/Util.hpp"

enum class State : uint8_t {
  IDLE,
  LEADER,
  BODY,
  TRAILER,
  FEED_OUT,
};

static volatile State state = State::IDLE;
static volatile uint16_t count = 0;

static TPC::Filesystem::Reader bodyReader;
static uint16_t bodyLength;
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

static void goToFeedOut_ID() {
  state = State::FEED_OUT;
}

static void refillDataBuffer_IE() {
  bool bufferFull;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    bufferFull = TPC::TPDataBuffer::full_ID();
  }

  while (!bufferFull && bodyLength && !bodyReader.eof()) {
    const uint8_t asciiChar = *bodyReader.pointer();
    bodyReader.advance(1);
    bodyLength--;

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
            TPC::TPDataBuffer::push_ID(tapeCode);
            bufferFull = TPC::TPDataBuffer::full_ID();
          }
        }
        break;
      }
    }
  }
}

static void scheduleTask() {
  TPC::Scheduler::schedule(
    TPC::Scheduler::TaskID::TP_DATA_PROVIDER_SERVICE,
    TPC::Timekeeping::Interval::fromMilliseconds(50)
  );
}

void TPC::TPDataProvider::init() {
  scheduleTask();
}

void TPC::TPDataProvider::setPrintJob_IE(TPC::Filesystem::Reader reader, uint16_t length) {
  bodyReader = reader;
  bodyLength = length;
  refillDataBuffer_IE();
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    goToLeader_ID();
  }
  LOG(DEBUG, "[TPDataProvider] print job added or changed");
}

void TPC::TPDataProvider::setFeedOutJob_IE() {
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    goToFeedOut_ID();
  }
  LOG(DEBUG, "[TPDataProvider] feed-out job added or changed");
}

void TPC::TPDataProvider::clearJob_IE() {
  bodyLength = 0;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    TPC::TPDataBuffer::reset_ID();
    goToIdle_ID();
  }
  LOG(DEBUG, "[TPDataProvider] job cleared");
}

void TPC::TPDataProvider::serviceTask_IE() {
  refillDataBuffer_IE();
  scheduleTask();
}

TPC::Util::MaybeUint8 TPC::TPDataProvider::nextByte_ID() {
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
      TPC::Util::MaybeUint8 result = TPC::TPDataBuffer::pop_ID();
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
    case State::FEED_OUT: {
      return TPC::Util::MaybeUint8(true, 0);
    }
  }
  // Should be unreachable.
  return TPC::Util::MaybeUint8(false);
}
