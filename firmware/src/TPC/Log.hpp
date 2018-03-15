#ifndef __TPC_LOG_HPP
#define __TPC_LOG_HPP

#include <stdint.h>

#include <avr/pgmspace.h>

#include "TPC/Filesystem.hpp"

namespace TPC {
  namespace Log {
    void init();

    void writeChar(char c);
    void writeNewline();
    void writeString(const char * str);
    void writeString(const char * str, uint8_t len);
    void writeStringP(PGM_P str);
    void writeFilename(TPC::Filesystem::DirectoryEntry * entry);
    void writeHex4(uint8_t val);
    void writeHex8(uint8_t val);
    void writeHex16(uint16_t val);

    void log(PGM_P str);
    void log(PGM_P str, uint8_t val);
    void log(PGM_P str, uint16_t val);
    void log(PGM_P str, TPC::Filesystem::DirectoryEntry * entry);
  }
}

#define LOG(STR, ...) { \
  static const char str[] PROGMEM = STR; \
  TPC::Log::log(str,##__VA_ARGS__); \
}

#endif
