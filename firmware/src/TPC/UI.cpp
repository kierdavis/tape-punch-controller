#include <stdint.h>

#include <util/atomic.h>

#include "TPC/ButtonsDriver.hpp"
#include "TPC/FileSelector.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/LCD.hpp"
#include "TPC/Log.hpp"
#include "TPC/TPController.hpp"
#include "TPC/UI.hpp"

enum class State : uint8_t {
  IDLE,
  PRINT,
};

static volatile State state = State::IDLE;

void TPC::UI::init() {
  TPC::ButtonsDriver::init();
  TPC::LCD::init();
  state = State::IDLE;
  TPC::UI::refresh_IE();
}

void TPC::UI::refresh_IE() {
  TPC::LCD::clear();
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
        TPC::LCD::writeAt(0, 0, nameBuffer);
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

static void setState(State newState) {
  state = newState;
  TPC::UI::refresh_IE();
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

static void checkIfDonePrinting_IE() {
  if (!TPC::TPController::isOn_IE()) {
    LOG("[UI] printing complete");
    setState(State::IDLE);
  }
}

void TPC::UI::tick_IE() {
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
}

static void confirm_IE() {
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

static void cancel_IE() {
  LOG("[UI] CANCEL pressed");
  switch (state) {
    case State::IDLE: {
      TPC::FileSelector::selectNext();
      TPC::UI::refresh_IE();
      break;
    }
    case State::PRINT: {
      // TODO: abort
      break;
    }
  }
}

static void both_IE() {
  LOG("[UI] CONFIRM+CANCEL pressed");
}

void TPC::UI::Hooks::confirm_ID() {
  NONATOMIC_BLOCK(NONATOMIC_FORCEOFF) {
    confirm_IE();
  }
}

void TPC::UI::Hooks::cancel_ID() {
  NONATOMIC_BLOCK(NONATOMIC_FORCEOFF) {
    cancel_IE();
  }
}

void TPC::UI::Hooks::both_ID() {
  NONATOMIC_BLOCK(NONATOMIC_FORCEOFF) {
    both_IE();
  }
}
