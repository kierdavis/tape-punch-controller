#include <stdint.h>

#include "Controller/Job.hpp"

Controller::Job::Job(uint16_t length, const uint8_t * dataBuffer)
  : length(length),
    dataBuffer(dataBuffer),
    dataPtr(dataBuffer),
    next(nullptr) {}
