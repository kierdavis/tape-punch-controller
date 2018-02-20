#include <stdint.h>

#include "TPC/TPController.hpp"
#include "TPC/SerialDriver.hpp"
#include "TPC/UIButtonsDriver.hpp"
#include "UI/FileList.hpp"
#include "UI/UIController.hpp"
#include "TPC/BlockStorage.hpp"

enum class State : uint8_t {
  IDLE,
  PRINTING,
};

static State state = State::IDLE;

void UI::UIController::init() {
  TPC::UIButtonsDriver::init();
  state = State::IDLE;
}

void UI::UIController::Hooks::confirm() {
  switch (state) {
    case State::IDLE: {
      USBInterface::FAT::DirectoryEntry * file = UI::FileList::selected();
      if (file != nullptr) {
        // TODO: doesn't support files spread across multiple clusters.
        uint8_t * contents = TPC::BlockStorage::get(file->startCluster + USBInterface::FAT::NUM_RESERVED_SECTORS);
        uint16_t length = file->size;
        SERIAL_WRITE("Printing file 0x");
        TPC::SerialDriver::writeHex16((uint16_t) file);
        SERIAL_WRITE(" (contents at cluster 0x");
        TPC::SerialDriver::writeHex16(file->startCluster);
        SERIAL_WRITE(" / addr 0x");
        TPC::SerialDriver::writeHex16((uint16_t) contents);
        SERIAL_WRITE(")\r\n");
        // TODO: check if already processing a job
        TPC::TPController::setJob_IE(length, contents);
        state = State::PRINTING;
      }
      break;
    }
    case State::PRINTING: {
      break;
    }
  }
}

void UI::UIController::Hooks::cancel() {

}

void UI::UIController::Hooks::both() {

}
