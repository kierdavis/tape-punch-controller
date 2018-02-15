#ifndef __TPC_USB_INTERFACE_SCSI_HPP
#define __TPC_USB_INTERFACE_SCSI_HPP

#include <stdbool.h>

#include <LUFA/Drivers/USB/USB.h>

namespace USBInterface {
  namespace SCSI {
    bool handle(MS_CommandBlockWrapper_t * const commandBlock);
  }
}

#endif
