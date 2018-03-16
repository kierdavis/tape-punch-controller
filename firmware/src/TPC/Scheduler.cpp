#include <stdbool.h>
#include <stdint.h>

#include "TPC/Scheduler.hpp"
#include "TPC/Timekeeping.hpp"

#include "TPC/TPJobManager.hpp"
#include "TPC/UI.hpp"
#include "TPC/USBDriver.hpp"

using TPC::Scheduler::TaskID;
using TPC::Timekeeping::Interval;
using TPC::Timekeeping::Timestamp;

class ScheduledTaskSet {
protected:
  uint8_t bitSet;
public:
  static constexpr uint8_t CAPACITY = sizeof(bitSet) * 8;
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

static constexpr uint8_t NUM_TASKS = ScheduledTaskSet::CAPACITY;

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

void TPC::Scheduler::cancel(TaskID taskID) {
  scheduledTasks.remove(taskID);
}

static void serviceTask(TaskID taskID) {
  switch (taskID) {
    case TaskID::TP_JOB_MANAGER: {
      TPC::TPJobManager::serviceTask_IE();
      break;
    }
    case TaskID::UI: {
      TPC::UI::serviceTask_IE();
      break;
    }
    case TaskID::USB_DRIVER: {
      TPC::USBDriver::serviceTask();
      break;
    }
  }
}

void TPC::Scheduler::serviceTasks() {
  for (uint8_t i = 0; i < NUM_TASKS; i++) {
    TaskID taskID = (TaskID) i;
    if (scheduledTasks.contains(taskID) && timestamps.get(taskID).isBefore(Timestamp::now())) {
      scheduledTasks.remove(taskID);
      serviceTask(taskID);
    }
  }
}
