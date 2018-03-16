#ifndef __TPC_TP_JOB_MANAGER_HPP
#define __TPC_TP_JOB_MANAGER_HPP

#include <stdint.h>

#include "TPC/Filesystem.hpp"
#include "TPC/Util.hpp"

namespace TPC {
  namespace TPJobManager {
    void init();
    void setJob_IE(TPC::Filesystem::Reader reader, uint16_t length);
    void clearJob_IE();
    void serviceTask_IE();
    TPC::Util::MaybeUint8 nextByte_ID();
  }
}

#endif
