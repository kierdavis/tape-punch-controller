#ifndef __TPC_USB_INTERFACE_DESCRIPTOR_HPP
#define __TPC_USB_INTERFACE_DESCRIPTOR_HPP

#include <stdbool.h>
#include <stdint.h>

#include <LUFA/Drivers/USB/USB.h>

namespace USBInterface {
  namespace USBDescriptor {
    enum class InterfaceNumber : uint8_t {
      MASS_STORAGE = 0,
    };

    enum class StringNumber : uint8_t {
      LANGUAGE = 0,
      MANUFACTURER = 1,
      PRODUCT = 2,
    };

    enum class EndpointAddr : uint8_t {
      MASS_STORAGE_IN = ENDPOINT_DIR_IN | 3,
      MASS_STORAGE_OUT = ENDPOINT_DIR_OUT | 4,
    };

    static const uint16_t MASS_STORAGE_EPSIZE = 64;

    class Ref {
    public:
      const void * pointer;
      uint16_t size;
      uint8_t memorySpace; // possible values listed in USB_DescriptorMemorySpaces_t.
    };

    bool lookup(uint8_t type,
                uint8_t number,
                uint16_t index,
                Ref * dest);
  }
}

#endif
