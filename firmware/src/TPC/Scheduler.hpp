#ifndef __TPC_SCHEDULER_HPP
#define __TPC_SCHEDULER_HPP

#include <stdint.h>

#include "TPC/Timekeeping.hpp"

namespace TPC {
  namespace Scheduler {
    enum class TaskID : uint8_t {
      TP_DATA_PROVIDER_SERVICE,
      UI_BOTH_BUTTONS,
      UI_CANCEL_BUTTON,
      UI_CONFIRM_BUTTON,
      UI_SERVICE,
      USB_DRIVER_SERVICE,
    };

    void init();
    void schedule(TaskID taskID, TPC::Timekeeping::Timestamp when);
    void schedule(TaskID taskID, TPC::Timekeeping::Interval delay);
    void schedule(TaskID taskID);
    void cancel(TaskID taskID);
    void serviceTasks();
  }
}

#endif
