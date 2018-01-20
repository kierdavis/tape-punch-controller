#ifndef __TPC_IO_PORT_HPP
#define __TPC_IO_PORT_HPP

namespace IO {
  enum class Port {
    #if PLATFORM == IL_MATTO
      A, B, C, D
    #else
      #error "invalid or unsupported PLATFORM"
    #endif
  };
}

#endif
