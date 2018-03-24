#include <stdint.h>

#include "TPC/Application.hpp"
#include "TPC/FileSelector.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"
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

void TPC::Application::init() {
  TPC::Filesystem::init();
  TPC::USBDriver::init();
  TPC::TPController::init();
  TPC::UI::init();
  setState_IE(State::IDLE);
}

void TPC::Application::returnToIdle_IE() {
  setState_IE(State::IDLE);
}

void TPC::Application::tryStartPrinting_IE(bool ignoreLowTape) {
  TPC::Filesystem::DirectoryEntry * selectedFile = TPC::FileSelector::selected();
  if (selectedFile != nullptr) {
    if (TPC::TPController::readNoTapeSensor()) {
      LOG("[Application] no tape warning");
      setState_IE(State::IDLE_NO_TAPE_WARNING);
    }
    else if (!ignoreLowTape && TPC::TPController::readLowTapeSensor()) {
      LOG("[Application] low tape warning");
      setState_IE(State::IDLE_LOW_TAPE_WARNING);
    }
    else {
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
}

void TPC::Application::stopPrinting_IE() {
  LOG("[Application] printing cancelled");
  TPC::TPController::clearJob_IE();
  setState_IE(State::IDLE);
}

void TPC::Application::selectNextFile_IE() {
  TPC::FileSelector::selectNext();
  TPC::UI::refresh_IE();
}

void TPC::Application::printingComplete_IE() {
  LOG("[Application] printing complete");
  setState_IE(State::IDLE);
}
