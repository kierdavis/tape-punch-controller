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
      LOG(INFO, "[Application] no tape warning");
      setState_IE(State::IDLE_NO_TAPE_WARNING);
    }
    else if (!ignoreLowTape && TPC::TPController::readLowTapeSensor()) {
      LOG(INFO, "[Application] low tape warning");
      setState_IE(State::IDLE_LOW_TAPE_WARNING);
    }
    else {
      uint32_t size32 = selectedFile->file.size;
      if (size32 > 0xFFFF) {
        LOG(IMPORTANT, "[Application] WARNING: file larger than 0xFFFF bytes, truncating!");
        size32 = 0xFFFF;
      }
      uint16_t size = (uint16_t) size32;
      TPC::Filesystem::BlockNumber start = TPC::Filesystem::BlockNumber::fromCluster(selectedFile->file.startCluster);
      TPC::Filesystem::Reader reader(start);
      LOG(INFO, "[Application] printing ", selectedFile);
      // TODO: check if already processing a job
      TPC::TPController::setPrintJob_IE(reader, size);
      setState_IE(State::PRINT);
    }
  }
}

void TPC::Application::stopPrinting_IE() {
  LOG(INFO, "[Application] printing cancelled");
  TPC::TPController::clearJob_IE();
  setState_IE(State::IDLE);
}

void TPC::Application::warnNoTapeDuringPrint_IE() {
  LOG(INFO, "[Application] no tape warning (during print)")
  TPC::TPController::clearJob_IE();
  setState_IE(State::IDLE_NO_TAPE_WARNING);
}

void TPC::Application::warnLowTapeDuringPrint_IE() {
  LOG(INFO, "[Application] low tape warning (during print)")
  setState_IE(State::PRINT_LOW_TAPE_WARNING);
}

void TPC::Application::selectNextFile_IE() {
  TPC::FileSelector::selectNext();
  TPC::UI::refresh_IE();
}

void TPC::Application::printingComplete_IE() {
  LOG(INFO, "[Application] printing complete");
  setState_IE(State::IDLE);
}

void TPC::Application::openMenu_IE() {
  LOG(INFO, "[Application] menu opened");
  setState_IE(State::MENU_FEED_OUT);
}

void TPC::Application::closeMenu_IE() {
  LOG(INFO, "[Application] menu closed");
  setState_IE(State::IDLE);
}

void TPC::Application::startFeedOut_IE() {
  LOG(INFO, "[Application] starting feed out");
  TPC::TPController::setFeedOutJob_IE();
  setState_IE(State::FEED_OUT);
}

void TPC::Application::stopFeedOut_IE() {
  LOG(INFO, "[Application] stopping feed out");
  TPC::TPController::clearJob_IE();
  setState_IE(State::MENU_FEED_OUT);
}
