#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/atomic.h>

#include "Controller/Job.hpp"
#include "Controller/JobList.hpp"
#include "Controller/JobQueue.hpp"
#include "Util/Panic.hpp"

static Controller::JobList queue;
static Controller::JobList toBeFreed;

void Controller::JobQueue::addJob_IE(uint16_t length, const uint8_t * buffer) {
  Controller::Job * job = (Controller::Job *) malloc(sizeof(Controller::Job));
  if (!job) {
    Util::Panic::memory();
  }
  *job = Controller::Job(length, buffer);
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    // Interrupts disabled within this block.
    queue.pushBack(job);
  }
}

Controller::JobQueue::PopByteResult Controller::JobQueue::popByte_ID() {
  Controller::JobQueue::PopByteResult result = { .hasData = false, .data = 0 };
  Job * job = queue.getFront();
  while (job != nullptr && job->length == 0) {
    queue.popFront();
    toBeFreed.pushFront(job);
    job = queue.getFront();
  }
  if (job != nullptr) {
    result.hasData = true;
    const uint8_t * dataPtr = job->dataPtr;
    if (dataPtr != nullptr) {
      result.data = *dataPtr;
      job->dataPtr = dataPtr + 1;
    }
    job->length--;
  }
  return result;
}

void Controller::JobQueue::tick_IE() {
  while (1) {
    Job * job;
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
      job = toBeFreed.popFront();
    }
    if (job == nullptr) {
      break;
    } else {
      free(job);
      job = nullptr;
    }
  }
}
