#include <stdint.h>

#include "TPC/Application.hpp"
#include "TPC/ButtonsDriver.hpp"
#include "TPC/FileSelector.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/LCDDriver.hpp"
#include "TPC/LCDActionLine.hpp"
#include "TPC/LCDStatusLine.hpp"
#include "TPC/Log.hpp"
#include "TPC/UI.hpp"

using TPC::Application::State;

void TPC::UI::init() {
  TPC::ButtonsDriver::init();
  TPC::LCDDriver::init();
}

void TPC::UI::refresh_IE() {
  switch (TPC::Application::getState_IE()) {
    case State::IDLE: {
      TPC::Filesystem::DirectoryEntry * selectedFile = TPC::FileSelector::selected();
      if (selectedFile == nullptr) {
        SET_LCD_STATUS_LINE("No files loaded");
        SET_LCD_ACTION_LINE("", "");
      }
      else {
        TPC::LCDStatusLine::clear();
        TPC::Filesystem::formatName(selectedFile, TPC::LCDStatusLine::getBuffer());
        TPC::LCDStatusLine::finishAppending();
        SET_LCD_ACTION_LINE("NEXT", "PRINT");
      }
      break;
    }
    case State::IDLE_NO_TAPE_WARNING: {
      SET_LCD_STATUS_LINE("Out of tape!");
      SET_LCD_ACTION_LINE("", "OK");
      break;
    }
    case State::IDLE_LOW_TAPE_WARNING: {
      SET_LCD_STATUS_LINE("Low on tape, proceed?");
      SET_LCD_ACTION_LINE("NO", "YES");
      break;
    }
    case State::PRINT: {
      SET_LCD_STATUS_LINE("Printing...");
      SET_LCD_ACTION_LINE("CANCEL", "");
      break;
    }
    case State::PRINT_LOW_TAPE_WARNING: {
      SET_LCD_STATUS_LINE("Printing... (low on tape)");
      SET_LCD_ACTION_LINE("CANCEL", "");
      break;
    }
    case State::MENU_FEED_OUT: {
      SET_LCD_STATUS_LINE("Menu: feed out");
      SET_LCD_ACTION_LINE("EXIT", "SELECT");
      break;
    }
    case State::FEED_OUT: {
      SET_LCD_STATUS_LINE("Feeding tape...");
      SET_LCD_ACTION_LINE("STOP", "");
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
    case State::MENU_FEED_OUT: {
      TPC::Application::startFeedOut_IE();
      break;
    }
    case State::FEED_OUT: {
      TPC::Application::stopFeedOut_IE();
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
    case State::MENU_FEED_OUT: {
      TPC::Application::closeMenu_IE();
      break;
    }
    case State::FEED_OUT: {
      TPC::Application::stopFeedOut_IE();
      break;
    }
  }
}

void TPC::UI::handleBothButtons_IE() {
  LOG(DEBUG, "[UI] CONFIRM+CANCEL pressed");
  switch (TPC::Application::getState_IE()) {
    case State::IDLE:
    case State::IDLE_NO_TAPE_WARNING:
    case State::IDLE_LOW_TAPE_WARNING: {
      TPC::Application::openMenu_IE();
      break;
    }
    case State::MENU_FEED_OUT: {
      // For now, do nothing.
      break;
    }
    default: {
      // Do nothing.
      break;
    }
  }
}
