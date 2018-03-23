#ifndef __TPC_TP_DATA_PROVIDER_HPP
#define __TPC_TP_DATA_PROVIDER_HPP

#include <stdint.h>

#include "TPC/Filesystem.hpp"
#include "TPC/Util.hpp"

namespace TPC {
  namespace TPDataProvider {
    void init();
    void setJob_IE(TPC::Filesystem::Reader reader, uint16_t length);
    void clearJob_IE();
    void serviceTask_IE();
    TPC::Util::MaybeUint8 nextByte_ID();
  }
}

#endif
