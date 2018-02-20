#ifndef __TPC_TPC_SCSI_HPP
#define __TPC_TPC_SCSI_HPP

#include <stdbool.h>

#include <LUFA/Drivers/USB/USB.h>

namespace TPC {
  namespace SCSI {
    bool handle(MS_CommandBlockWrapper_t * const commandBlock);
  }
}

#endif
