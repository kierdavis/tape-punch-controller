#include <stdint.h>

#include <util/atomic.h>

#include "TPC/ButtonsDriver.hpp"
#include "TPC/FileSelector.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/LCDDriver.hpp"
#include "TPC/Log.hpp"
#include "TPC/Scheduler.hpp"
#include "TPC/Timekeeping.hpp"
#include "TPC/TPController.hpp"
#include "TPC/UI.hpp"

enum class State : uint8_t {
  IDLE,
  PRINT,
};

static volatile State state = State::IDLE;

static void setState(State newState) {
  state = newState;
  TPC::UI::refresh_IE();
}

static void scheduleTask() {
  TPC::Scheduler::schedule(
    TPC::Scheduler::TaskID::UI_SERVICE,
    TPC::Timekeeping::Interval::fromMilliseconds(100)
  );
}

void TPC::UI::init() {
  TPC::ButtonsDriver::init();
  TPC::LCDDriver::init();
  setState(State::IDLE);
  scheduleTask();
}

void TPC::UI::refresh_IE() {
  TPC::LCDDriver::clear();
  switch (state) {
    case State::IDLE: {
      TPC::Filesystem::DirectoryEntry * selectedFile = TPC::FileSelector::selected();
      if (selectedFile == nullptr) {
        LCD_WRITE_AT(0, 0, "No files present");
      }
      else {
        static constexpr uint8_t NAME_BUFFER_LEN = 17;
        char nameBuffer[NAME_BUFFER_LEN];
        selectedFile->formatName(nameBuffer, NAME_BUFFER_LEN);
        TPC::LCDDriver::writeAt(0, 0, nameBuffer);
        LCD_WRITE_AT(1, 0, "[NEXT]");
        LCD_WRITE_AT(1, 16-7, "[PRINT]");
      }
      break;
    }
    case State::PRINT: {
      LCD_WRITE_AT(0, 0, "Printing");
      break;
    }
  }
}

static void startPrinting_IE() {
  TPC::Filesystem::DirectoryEntry * selectedFile = TPC::FileSelector::selected();
  if (selectedFile != nullptr) {
    uint32_t size32 = selectedFile->size;
    if (size32 > 0xFFFF) {
      LOG("[UI] WARNING: file larger than 0xFFFF bytes, truncating!");
      size32 = 0xFFFF;
    }
    uint16_t size = (uint16_t) size32;
    uint16_t firstCluster = selectedFile->startCluster + TPC::Filesystem::NUM_RESERVED_SECTORS;
    TPC::Filesystem::Reader reader(firstCluster);
    LOG("[UI] printing ", selectedFile);
    // TODO: check if already processing a job
    TPC::TPController::setJob_IE(reader, size);
    setState(State::PRINT);
  }
}

static void cancelPrinting_IE() {
  TPC::TPController::clearJob_IE();
  setState(State::IDLE);
  LOG("[UI] printing cancelled");
}

static void checkIfDonePrinting_IE() {
  if (!TPC::TPController::isOn_IE()) {
    LOG("[UI] printing complete");
    setState(State::IDLE);
  }
}

void TPC::UI::serviceTask_IE() {
  switch (state) {
    case State::IDLE: {
      // Do nothing.
      break;
    }
    case State::PRINT: {
      checkIfDonePrinting_IE();
      break;
    }
  }
  scheduleTask();
}

void TPC::UI::handleConfirmButton_IE() {
  LOG("[UI] CONFIRM pressed");
  switch (state) {
    case State::IDLE: {
      startPrinting_IE();
      break;
    }
    case State::PRINT: {
      // Do nothing.
      break;
    }
  }
}

void TPC::UI::handleCancelButton_IE() {
  LOG("[UI] CANCEL pressed");
  switch (state) {
    case State::IDLE: {
      TPC::FileSelector::selectNext();
      TPC::UI::refresh_IE();
      break;
    }
    case State::PRINT: {
      cancelPrinting_IE();
      break;
    }
  }
}

void TPC::UI::handleBothButtons_IE() {
  LOG("[UI] CONFIRM+CANCEL pressed");
}
