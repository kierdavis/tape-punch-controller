#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#include "Config.hpp"
#include "TPC/USBDescriptor.hpp"

using namespace TPC::USBDescriptor;

class ConfigurationDescriptor {
public:
  USB_Descriptor_Configuration_Header_t header;
  USB_Descriptor_Interface_t msInterface;
  USB_Descriptor_Endpoint_t msDataInEndpoint;
  USB_Descriptor_Endpoint_t msDataOutEndpoint;
};

static const USB_Descriptor_Device_t deviceDescriptor PROGMEM = {
  .Header = {
    .Size = sizeof(USB_Descriptor_Device_t),
    .Type = DTYPE_Device,
  },
  .USBSpecification = VERSION_BCD(1,1,0),
  .Class = USB_CSCP_NoDeviceClass,
  .SubClass = USB_CSCP_NoDeviceSubclass,
  .Protocol = USB_CSCP_NoDeviceProtocol,
  .Endpoint0Size = FIXED_CONTROL_ENDPOINT_SIZE,
  .VendorID = Config::USB_VENDOR_ID,
  .ProductID = Config::USB_PRODUCT_ID,
  .ReleaseNumber = VERSION_BCD(0,0,1),
  .ManufacturerStrIndex = (uint8_t) StringNumber::MANUFACTURER,
  .ProductStrIndex = (uint8_t) StringNumber::PRODUCT,
  .SerialNumStrIndex = USE_INTERNAL_SERIAL,
  .NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS,
};

static const ConfigurationDescriptor configurationDescriptor PROGMEM = {
  .header = {
    .Header = {
      .Size = sizeof(USB_Descriptor_Configuration_Header_t),
      .Type = DTYPE_Configuration,
    },
    .TotalConfigurationSize = sizeof(ConfigurationDescriptor),
    .TotalInterfaces = 1,
    .ConfigurationNumber = 1,
    .ConfigurationStrIndex = NO_DESCRIPTOR,
    .ConfigAttributes = USB_CONFIG_ATTR_SELFPOWERED | USB_CONFIG_ATTR_RESERVED,
    .MaxPowerConsumption = USB_CONFIG_POWER_MA(10), // Very lenient
  },
  .msInterface = {
    .Header = {
      .Size = sizeof(USB_Descriptor_Interface_t),
      .Type = DTYPE_Interface,
    },
    .InterfaceNumber = (uint8_t) InterfaceNumber::MASS_STORAGE,
    .AlternateSetting = 0,
    .TotalEndpoints = 2,
    .Class = MS_CSCP_MassStorageClass,
    .SubClass = MS_CSCP_SCSITransparentSubclass,
    .Protocol = MS_CSCP_BulkOnlyTransportProtocol,
    .InterfaceStrIndex = NO_DESCRIPTOR,
  },
  .msDataInEndpoint = {
    .Header = {
      .Size = sizeof(USB_Descriptor_Endpoint_t),
      .Type = DTYPE_Endpoint,
    },
    .EndpointAddress = (uint8_t) EndpointAddr::MASS_STORAGE_IN,
    .Attributes = EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA,
    .EndpointSize = MASS_STORAGE_EPSIZE,
    .PollingIntervalMS = 0x05,
  },
  .msDataOutEndpoint = {
    .Header = {
      .Size = sizeof(USB_Descriptor_Endpoint_t),
      .Type = DTYPE_Endpoint,
    },
    .EndpointAddress = (uint8_t) EndpointAddr::MASS_STORAGE_OUT,
    .Attributes = EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA,
    .EndpointSize = MASS_STORAGE_EPSIZE,
    .PollingIntervalMS = 0x05,
  },
};

#define DEFINE_STRING(NAME, VALUE) \
  static const struct NAME##_t { \
    USB_Descriptor_Header_t Header; \
    wchar_t UnicodeString[sizeof(VALUE)/sizeof(wchar_t)]; /* Size includes trailing NULL here */ \
  } NAME PROGMEM = { \
    { \
      sizeof(struct NAME##_t) - 2, /* Size does not need to include trailing NULL here */ \
      DTYPE_String, \
    }, \
    VALUE, \
  }

#define DEFINE_STRING_ARRAY(NAME, ...) \
  static const struct NAME##_t { \
    USB_Descriptor_Header_t Header; \
    uint16_t UnicodeString[sizeof((uint16_t) {__VA_ARGS__})/sizeof(uint16_t)]; \
  } NAME PROGMEM = { \
    { \
      sizeof(struct NAME##_t), \
      DTYPE_String, \
    }, \
    {__VA_ARGS__}, \
  }

static const USB_Descriptor_String_t * lookupString(uint8_t number) {
  switch ((StringNumber) number) {
    case StringNumber::LANGUAGE: {
      // The contents of this string descriptor are actually an array of 16-bit integers.
      // Each element of the array identifies a language supported by the device.
      DEFINE_STRING_ARRAY(languageString, LANGUAGE_ID_ENG);
      return (const USB_Descriptor_String_t *) &languageString;
    }
    case StringNumber::MANUFACTURER: {
      DEFINE_STRING(manufacturerString, L"Kier Davis");
      return (const USB_Descriptor_String_t *) &manufacturerString;
    }
    case StringNumber::PRODUCT: {
      DEFINE_STRING(productString, L"Tape punch controller");
      return (const USB_Descriptor_String_t *) &productString;
    }
    default: {
      return nullptr;
    }
  }
}

bool TPC::USBDescriptor::lookup(uint8_t type, uint8_t number, uint16_t index, Ref * ref) {
  switch (type) {
    case DTYPE_Device: {
      ref->pointer = &deviceDescriptor;
      ref->size = sizeof(deviceDescriptor);
      ref->memorySpace = MEMSPACE_FLASH;
      return true;
    }
    case DTYPE_Configuration: {
      ref->pointer = &configurationDescriptor;
      ref->size = sizeof(configurationDescriptor);
      ref->memorySpace = MEMSPACE_FLASH;
      return true;
    }
    case DTYPE_String: {
      const USB_Descriptor_String_t * desc = lookupString(number);
      if (desc != nullptr) {
        ref->pointer = desc;
        ref->size = pgm_read_byte(&desc->Header.Size);
        ref->memorySpace = MEMSPACE_FLASH;
        return true;
      }
    }
  }

  return false;
}
