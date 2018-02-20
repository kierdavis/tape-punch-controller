#include <stdint.h>

#include <util/atomic.h>

#include "TPC/Application.hpp"
#include "TPC/BlockStorage.hpp"
#include "TPC/ButtonsDriver.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/SerialDriver.hpp"
#include "TPC/TPController.hpp"
#include "UI/FileList.hpp"

enum class State : uint8_t {
  IDLE,
  PRINT,
};

static volatile State state = State::IDLE;

void TPC::Application::init() {
  TPC::ButtonsDriver::init();
  state = State::IDLE;
}

static void startPrinting_IE() {
  TPC::Filesystem::DirectoryEntry * selectedFile = UI::FileList::selected();
  if (selectedFile != nullptr) {
    // TODO: doesn't support files spread across multiple clusters
    uint8_t firstCluster = selectedFile->startCluster + TPC::Filesystem::NUM_RESERVED_SECTORS;
    uint8_t * fileData = TPC::BlockStorage::get(firstCluster);
    uint16_t length = selectedFile->size;
    SERIAL_WRITE("Printing\r\n");
    // TODO: check if already processing a job
    TPC::TPController::setJob_IE(length, fileData);
    state = State::PRINT;
  }
}

static void confirm_IE() {
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

}

static void both_IE() {

}

void TPC::Application::Hooks::confirm_ID() {
  NONATOMIC_BLOCK(NONATOMIC_FORCEOFF) {
    confirm_IE();
  }
}

void TPC::Application::Hooks::cancel_ID() {
  NONATOMIC_BLOCK(NONATOMIC_FORCEOFF) {
    cancel_IE();
  }
}

void TPC::Application::Hooks::both_ID() {
  NONATOMIC_BLOCK(NONATOMIC_FORCEOFF) {
    both_IE();
  }
}
