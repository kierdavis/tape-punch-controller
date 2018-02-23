#ifndef __TPC_LUFA_CONFIG_H
#define __TPC_LUFA_CONFIG_H

// Only include USB device-mode support (disables host-mode support).
#define USB_DEVICE_ONLY 1

// USB_OPT_RC32MCLKSRC: use the ~32MHz internal oscillator as the USB clock source
// USB_OPT_BUSEVENT_PRIMED: USB bus interrupt is medium priority
#define USE_STATIC_OPTIONS (USB_OPT_RC32MCLKSRC | USB_OPT_BUSEVENT_PRIHIGH)

// #define USE_FLASH_DESCRIPTORS

#define FIXED_CONTROL_ENDPOINT_SIZE 8

#define FIXED_NUM_CONFIGURATIONS 1

#define MAX_ENDPOINT_INDEX 4

#endif
