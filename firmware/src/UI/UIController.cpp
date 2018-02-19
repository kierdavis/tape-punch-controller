#include <stdint.h>

#include "Controller/TapePunch.hpp"
#include "Peripheral/Buttons.hpp"
#include "UI/FileList.hpp"
#include "UI/UIController.hpp"
#include "USBInterface/BlockStorage.hpp"
#include "Peripheral/Serial.hpp"

enum class State : uint8_t {
  IDLE,
  PRINTING,
};

static State state = State::IDLE;

void UI::UIController::init() {
  Peripheral::Buttons::init();
  state = State::IDLE;
}

void UI::UIController::Hooks::confirm() {
  switch (state) {
    case State::IDLE: {
      USBInterface::FAT::DirectoryEntry * file = UI::FileList::selected();
      if (file != nullptr) {
        // TODO: doesn't support files spread across multiple clusters.
        uint8_t * contents = USBInterface::BlockStorage::get(file->startCluster + USBInterface::FAT::NUM_RESERVED_SECTORS);
        uint16_t length = file->size;
        SERIAL_WRITE("Printing file 0x");
        Peripheral::Serial::writeHex16((uint16_t) file);
        SERIAL_WRITE(" (contents at cluster 0x");
        Peripheral::Serial::writeHex16(file->startCluster);
        SERIAL_WRITE(" / addr 0x");
        Peripheral::Serial::writeHex16((uint16_t) contents);
        SERIAL_WRITE(")\r\n");
        Controller::TapePunch::addJob_IE(100);
        Controller::TapePunch::addJob_IE(length, contents);
        Controller::TapePunch::addJob_IE(150);
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
