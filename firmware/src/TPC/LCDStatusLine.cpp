#include <stdint.h>

#include <avr/pgmspace.h>

#include "TPC/LCDDriver.hpp"
#include "TPC/LCDStatusLine.hpp"
#include "TPC/Log.hpp"
#include "TPC/Scheduler.hpp"
#include "TPC/Timekeeping.hpp"
#include "TPC/Util.hpp"

static constexpr uint8_t BUFFER_SIZE = 32;
static char text[BUFFER_SIZE];
static uint8_t textLength = 0;
static uint8_t scrollPos = 0;

static void scheduleTask() {
  if (textLength > 16) {
    uint8_t maxScrollPos = textLength - 16;
    TPC::Timekeeping::Interval duration = (scrollPos == 0 || scrollPos >= maxScrollPos)
      ? TPC::Timekeeping::Interval::fromSeconds(2)
      : TPC::Timekeeping::Interval::fromMilliseconds(500);
    TPC::Scheduler::schedule(TPC::Scheduler::TaskID::LCD_STATUS_LINE_SCROLL, duration);
  }
  else {
    // No need to scroll.
    TPC::Scheduler::cancel(TPC::Scheduler::TaskID::LCD_STATUS_LINE_SCROLL);
  }
}

static void render() {
  LOG(DEBUG_VERBOSE, "[LCDStatusLine] render scrollPos = 0x", scrollPos);
  TPC::LCDDriver::setCursorPos(0, 0);
  uint8_t column = 0;
  uint8_t index = scrollPos;
  while (column < 16 && index < textLength) {
    TPC::LCDDriver::writeData(text[index++]);
    column++;
  }
  while (column < 16) {
    TPC::LCDDriver::writeData(' ');
    column++;
  }
}

void TPC::LCDStatusLine::clear() {
  textLength = 0;
  scrollPos = 0;
}

void TPC::LCDStatusLine::append(const char * str) {
  while (textLength < BUFFER_SIZE) {
    char c = *(str++);
    if (c == '\0') {
      break;
    }
    text[textLength++] = c;
  }
}

void TPC::LCDStatusLine::appendP(const char * str) {
  while (textLength < BUFFER_SIZE) {
    char c = pgm_read_byte(str++);
    if (c == '\0') {
      break;
    }
    text[textLength++] = c;
  }
}

TPC::Util::CharArray TPC::LCDStatusLine::getBuffer() {
  return TPC::Util::CharArray(text, &textLength, BUFFER_SIZE);
}

void TPC::LCDStatusLine::finishAppending() {
  scrollPos = 0;
  scheduleTask();
  render();
}

void TPC::LCDStatusLine::scroll() {
  if (textLength > 16) {
    uint8_t maxScrollPos = textLength - 16;
    if (scrollPos >= maxScrollPos) {
      // Scroll was previously at the rightmost position; jump to leftmost position.
      scrollPos = 0;
    } else {
      // Scroll one character to the right.
      scrollPos++;
    }
  }
  scheduleTask();
  render();
}
