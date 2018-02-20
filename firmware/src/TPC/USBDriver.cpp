#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

#include "TPC/SerialDriver.hpp"
#include "TPC/USBDriver.hpp"
#include "USBInterface/USBDescriptor.hpp"
#include "USBInterface/SCSI.hpp"

// Encapsulates runtime state of Mass Storage interface.
static USB_ClassInfo_MS_Device_t msdInfo = {
  .Config = {
    .InterfaceNumber = (uint8_t) USBInterface::USBDescriptor::InterfaceNumber::MASS_STORAGE,
    .DataINEndpoint = {
      .Address = (uint8_t) USBInterface::USBDescriptor::EndpointAddr::MASS_STORAGE_IN,
      .Size    = USBInterface::USBDescriptor::MASS_STORAGE_EPSIZE,
      .Type    = EP_TYPE_BULK,
      .Banks   = 1,
    },
    .DataOUTEndpoint = {
      .Address = (uint8_t) USBInterface::USBDescriptor::EndpointAddr::MASS_STORAGE_OUT,
      .Size    = USBInterface::USBDescriptor::MASS_STORAGE_EPSIZE,
      .Type    = EP_TYPE_BULK,
      .Banks   = 1,
    },
    .TotalLUNs = 1,
  },
};

void TPC::USBDriver::init() {
  // Initialise LUFA.
  USB_Init();
}

void TPC::USBDriver::tick() {
  MS_Device_USBTask(&msdInfo);
  USB_USBTask();
}

// LUFA callbacks below.

extern "C" {
  void EVENT_USB_Device_Connect() {
    static const char str[] PROGMEM = "USB: enumerating\r\n";
    TPC::SerialDriver::writeStringP(str);
  }

  void EVENT_USB_Device_Disconnect() {
    static const char str[] PROGMEM = "USB: disconnected\r\n";
    TPC::SerialDriver::writeStringP(str);
  }

  void EVENT_USB_Device_ConfigurationChanged() {
    bool success = MS_Device_ConfigureEndpoints(&msdInfo);
    static const char successStr[] PROGMEM = "USB: configuration change successful.\r\n";
    static const char failureStr[] PROGMEM = "USB: configuration change unsuccessful.\r\n";
    TPC::SerialDriver::writeStringP(success ? successStr : failureStr);
    // TODO: actually handle `success`?
  }

  void EVENT_USB_Device_ControlRequest() {
    MS_Device_ProcessControlRequest(&msdInfo);
  }

  uint16_t CALLBACK_USB_GetDescriptor(uint16_t wValue,
                                      uint16_t wIndex,
                                      const void ** descriptorDest,
                                      uint8_t * memorySpaceDest) {
    uint8_t descriptorType = wValue >> 8;
    uint8_t descriptorNumber = wValue & 0xFF;
    USBInterface::USBDescriptor::Ref ref;
    bool ok = USBInterface::USBDescriptor::lookup(descriptorType, descriptorNumber, wIndex, &ref);
    if (ok) {
      *descriptorDest = ref.pointer;
      *memorySpaceDest = ref.memorySpace;
      return ref.size;
    } else {
      return NO_DESCRIPTOR;
    }
  }

  bool CALLBACK_MS_Device_SCSICommandReceived(USB_ClassInfo_MS_Device_t * msdInfo) {
    return USBInterface::SCSI::handle(&msdInfo->State.CommandBlock);
  }
};
