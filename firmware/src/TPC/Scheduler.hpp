#ifndef __TPC_SCHEDULER_HPP
#define __TPC_SCHEDULER_HPP

#include <stdint.h>

#include "TPC/Timekeeping.hpp"

namespace TPC {
  namespace Scheduler {
    enum class TaskID : uint8_t {
      APPLICATION_SERVICE,
      TP_DATA_PROVIDER_SERVICE,
      UI_BOTH_BUTTONS,
      UI_CANCEL_BUTTON,
      UI_CONFIRM_BUTTON,
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
