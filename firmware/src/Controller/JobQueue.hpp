#ifndef __TPC_CONTROLLER_JOB_QUEUE_HPP
#define __TPC_CONTROLLER_JOB_QUEUE_HPP

#include <stdbool.h>
#include <stdint.h>

#include "Controller/Job.hpp"

namespace Controller {
  namespace JobQueue {
    class PopByteResult {
    public:
      bool hasData;
      uint8_t data;
    };

    void addJob_IE(uint16_t length, const uint8_t * buffer = nullptr);
    PopByteResult popByte_ID();
    void tick_IE();
  }
}

#endif
