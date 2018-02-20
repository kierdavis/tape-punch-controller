#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "Controller/TapePunch.hpp"
#include "TPC/SerialDriver.hpp"
#include "TPC/MicrocontrollerDriver.hpp"
#include "UI/UIController.hpp"
#include "USBInterface/USBDevice.hpp"

static uint8_t const DATA[] = {
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00010,
  0b00100,
  0b01000,
  0b10000,
};

int main() {
  // First stage init.
  TPC::MicrocontrollerDriver::init();
  TPC::SerialDriver::init();

  static const char initStr1[] PROGMEM = "Init stage one complete.\r\n";
  TPC::SerialDriver::writeStringP(initStr1);

  // Second stage init.
  Controller::TapePunch::init();
  USBInterface::USBDevice::init();
  UI::UIController::init();
  sei();

  static const char initStr2[] PROGMEM = "Init stage two complete.\r\n";
  TPC::SerialDriver::writeStringP(initStr2);

  // Controller::TapePunch::addJob_IE(100); // leader (100 blank rows)
  // Controller::TapePunch::addJob_IE(sizeof(DATA)/sizeof(DATA[0]), DATA);
  // Controller::TapePunch::addJob_IE(200); // trailer (200 blank rows)

  while (1) {
    USBInterface::USBDevice::tick();
    _delay_us(1000);
  }
}
