#include <stdint.h>

#include "TPC/Application.hpp"
#include "TPC/FileSelector.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"
#include "TPC/Scheduler.hpp"
#include "TPC/Timekeeping.hpp"
#include "TPC/TPController.hpp"
#include "TPC/UI.hpp"
#include "TPC/USBDriver.hpp"

using TPC::Application::State;

static State state = State::IDLE;

State TPC::Application::getState_IE() {
  return state;
}

static void setState_IE(State newState) {
  state = newState;
  TPC::UI::refresh_IE();
}

static void scheduleTask() {
  TPC::Scheduler::schedule(
    TPC::Scheduler::TaskID::APPLICATION_SERVICE,
    TPC::Timekeeping::Interval::fromMilliseconds(100)
  );
}

void TPC::Application::init() {
  TPC::Filesystem::init();
  TPC::USBDriver::init();
  TPC::TPController::init();
  TPC::UI::init();
  setState_IE(State::IDLE);
  scheduleTask();
}

void TPC::Application::startPrinting_IE() {
  TPC::Filesystem::DirectoryEntry * selectedFile = TPC::FileSelector::selected();
  if (selectedFile != nullptr) {
    uint32_t size32 = selectedFile->size;
    if (size32 > 0xFFFF) {
      LOG("[Application] WARNING: file larger than 0xFFFF bytes, truncating!");
      size32 = 0xFFFF;
    }
    uint16_t size = (uint16_t) size32;
    uint16_t firstCluster = selectedFile->startCluster + TPC::Filesystem::NUM_RESERVED_SECTORS;
    TPC::Filesystem::Reader reader(firstCluster);
    LOG("[Application] printing ", selectedFile);
    // TODO: check if already processing a job
    TPC::TPController::setJob_IE(reader, size);
    setState_IE(State::PRINT);
  }
}

void TPC::Application::stopPrinting_IE() {
  TPC::TPController::clearJob_IE();
  setState_IE(State::IDLE);
  LOG("[Application] printing cancelled");
}

void TPC::Application::selectNextFile_IE() {
  TPC::FileSelector::selectNext();
  TPC::UI::refresh_IE();
}

static void checkIfDonePrinting_IE() {
  if (!TPC::TPController::isOn_IE()) {
    LOG("[Application] printing complete");
    setState_IE(State::IDLE);
  }
}

void TPC::Application::serviceTask_IE() {
  switch (TPC::Application::getState_IE()) {
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
