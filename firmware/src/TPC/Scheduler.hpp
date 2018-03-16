#ifndef __TPC_SCHEDULER_HPP
#define __TPC_SCHEDULER_HPP

#include <stdint.h>

#include "TPC/Timekeeping.hpp"

namespace TPC {
  namespace Scheduler {
    enum class TaskID : uint8_t {
      TP_JOB_MANAGER,
      UI,
      USB_DRIVER,
    };

    void init();
    void schedule(TaskID taskID, TPC::Timekeeping::Timestamp when);
    void schedule(TaskID taskID, TPC::Timekeeping::Interval delay);
    void cancel(TaskID taskID);
    void serviceTasks();
  }
}

#endif
