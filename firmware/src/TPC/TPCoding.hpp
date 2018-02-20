#ifndef __TPC_TP_CODING_HPP
#define __TPC_TP_CODING_HPP

#include <stdint.h>

namespace TPC {
  namespace TPCoding {
    static constexpr uint8_t UNPRINTABLE = 0xFF;
    static constexpr uint8_t BEGIN_COMMENT = 0xFE;
    static constexpr uint8_t END_COMMENT = 0xFD;
    uint8_t asciiToEdsac(char c);
  }
}

#endif
