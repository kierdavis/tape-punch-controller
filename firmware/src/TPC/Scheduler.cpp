#include <stdbool.h>
#include <stdint.h>

#include "TPC/Scheduler.hpp"
#include "TPC/Timekeeping.hpp"

#include "TPC/Application.hpp"
#include "TPC/TPController.hpp"
#include "TPC/TPDataProvider.hpp"
#include "TPC/UI.hpp"
#include "TPC/USBDriver.hpp"

using TPC::Scheduler::NUM_TASKS;
using TPC::Scheduler::TaskID;
using TPC::Timekeeping::Interval;
using TPC::Timekeeping::Timestamp;

class ScheduledTaskSet {
protected:
  uint8_t bitSet;
public:
  static constexpr uint8_t CAPACITY = sizeof(bitSet) * 8;
  static_assert(CAPACITY >= NUM_TASKS, "ScheduledTaskSet capacity too low; consider increasing width of ScheduledTaskSet::bitSet");
  ScheduledTaskSet() : bitSet(0) {}
  void clear() {
    bitSet = 0;
  }
  bool contains(TaskID taskID) {
    uint8_t index = (uint8_t) taskID;
    if (index < CAPACITY) {
      return bitSet & (1 << index);
    } else {
      return false;
    }
  }
  void add(TaskID taskID) {
    uint8_t index = (uint8_t) taskID;
    if (index < CAPACITY) {
      bitSet |= (1 << index);
    }
  }
  void remove(TaskID taskID) {
    uint8_t index = (uint8_t) taskID;
    if (index < CAPACITY) {
      bitSet &= ~(1 << index);
    }
  }
};

class TimestampMap {
protected:
  Timestamp timestamps[NUM_TASKS];
public:
  TimestampMap() {}
  Timestamp get(TaskID taskID) {
    uint8_t index = (uint8_t) taskID;
    if (index < NUM_TASKS) {
      return timestamps[index];
    } else {
      return Timestamp(0);
    }
  }
  void put(TaskID taskID, Timestamp timestamp) {
    uint8_t index = (uint8_t) taskID;
    if (index < NUM_TASKS) {
      timestamps[index] = timestamp;
    }
  }
};

static ScheduledTaskSet scheduledTasks;
static TimestampMap timestamps;

void TPC::Scheduler::init() {
  TPC::Timekeeping::init();
  scheduledTasks.clear();
}

void TPC::Scheduler::schedule(TaskID taskID, Timestamp when) {
  timestamps.put(taskID, when);
  scheduledTasks.add(taskID);
}

void TPC::Scheduler::schedule(TaskID taskID, Interval delay) {
  TPC::Scheduler::schedule(taskID, Timestamp::now().add(delay));
}

void TPC::Scheduler::schedule(TaskID taskID) {
  TPC::Scheduler::schedule(taskID, Interval(0));
}

void TPC::Scheduler::cancel(TaskID taskID) {
  scheduledTasks.remove(taskID);
}

static void serviceTask(TaskID taskID) {
  switch (taskID) {
    case TaskID::PRINTING_COMPLETE: {
      TPC::Application::printingComplete_IE();
    }
    case TaskID::TP_CONTROLLER_SERVICE: {
      TPC::TPController::serviceTask_IE();
      break;
    }
    case TaskID::TP_DATA_PROVIDER_SERVICE: {
      TPC::TPDataProvider::serviceTask_IE();
      break;
    }
    case TaskID::UI_BOTH_BUTTONS: {
      TPC::UI::handleBothButtons_IE();
      break;
    }
    case TaskID::UI_CANCEL_BUTTON: {
      TPC::UI::handleCancelButton_IE();
      break;
    }
    case TaskID::UI_CONFIRM_BUTTON: {
      TPC::UI::handleConfirmButton_IE();
      break;
    }
    case TaskID::USB_DRIVER_SERVICE: {
      TPC::USBDriver::serviceTask();
      break;
    }
  }
}

void TPC::Scheduler::serviceTasks() {
  for (uint8_t i = 0; i < NUM_TASKS; i++) {
    TaskID taskID = (TaskID) i;
    if (scheduledTasks.contains(taskID) && timestamps.get(taskID).isBeforeOrEqual(Timestamp::now())) {
      scheduledTasks.remove(taskID);
      serviceTask(taskID);
    }
  }
}
