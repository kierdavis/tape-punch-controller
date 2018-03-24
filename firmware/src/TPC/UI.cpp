#include <stdint.h>

#include "TPC/Application.hpp"
#include "TPC/ButtonsDriver.hpp"
#include "TPC/FileSelector.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/LCDDriver.hpp"
#include "TPC/Log.hpp"
#include "TPC/UI.hpp"

using TPC::Application::State;

void TPC::UI::init() {
  TPC::ButtonsDriver::init();
  TPC::LCDDriver::init();
}

void TPC::UI::refresh_IE() {
  TPC::LCDDriver::clear();
  switch (TPC::Application::getState_IE()) {
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
    case State::IDLE_NO_TAPE_WARNING: {
      LCD_WRITE_AT(0, 0, "No tape!");
      LCD_WRITE_AT(1, 16-4, "[OK]");
      break;
    }
    case State::IDLE_LOW_TAPE_WARNING: {
      LCD_WRITE_AT(0, 0, "Low tape! Proceed?");
      LCD_WRITE_AT(1, 0, "[NO]");
      LCD_WRITE_AT(1, 16-5, "[YES]");
      break;
    }
    case State::PRINT: {
      LCD_WRITE_AT(0, 0, "Printing");
      LCD_WRITE_AT(1, 0, "[CANCEL]");
      break;
    }
    case State::PRINT_LOW_TAPE_WARNING: {
      LCD_WRITE_AT(0, 0, "Printing (low tape!)");
      LCD_WRITE_AT(1, 0, "[CANCEL]");
      break;
    }
  }
}

void TPC::UI::handleConfirmButton_IE() {
  LOG(DEBUG, "[UI] CONFIRM pressed");
  switch (TPC::Application::getState_IE()) {
    case State::IDLE: {
      TPC::Application::tryStartPrinting_IE();
      break;
    }
    case State::IDLE_NO_TAPE_WARNING: {
      TPC::Application::returnToIdle_IE();
      break;
    }
    case State::IDLE_LOW_TAPE_WARNING: {
      TPC::Application::tryStartPrinting_IE(true);
      break;
    }
    case State::PRINT:
    case State::PRINT_LOW_TAPE_WARNING: {
      // Do nothing.
      break;
    }
  }
}

void TPC::UI::handleCancelButton_IE() {
  LOG(DEBUG, "[UI] CANCEL pressed");
  switch (TPC::Application::getState_IE()) {
    case State::IDLE: {
      TPC::Application::selectNextFile_IE();
      break;
    }
    case State::IDLE_NO_TAPE_WARNING:
    case State::IDLE_LOW_TAPE_WARNING: {
      TPC::Application::returnToIdle_IE();
      break;
    }
    case State::PRINT:
    case State::PRINT_LOW_TAPE_WARNING: {
      TPC::Application::stopPrinting_IE();
      break;
    }
  }
}

void TPC::UI::handleBothButtons_IE() {
  LOG(DEBUG, "[UI] CONFIRM+CANCEL pressed");
}
