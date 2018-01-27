#ifndef __TPC_CONTROLLER_JOB_HPP
#define __TPC_CONTROLLER_JOB_HPP

#include <stdint.h>

namespace Controller {
  class Job {
  public:
    uint16_t length;
    const uint8_t * dataBuffer;
    const uint8_t * dataPtr;
    Job * next;

    Job(uint16_t length, const uint8_t * dataBuffer = nullptr);
  };
}

#endif
