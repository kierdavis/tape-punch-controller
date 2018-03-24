#ifndef __TPC_LOG_HPP
#define __TPC_LOG_HPP

#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

#include "TPC/Filesystem.hpp"

namespace TPC {
  namespace Log {
    enum class Level : uint8_t {
      SILENT,
      IMPORTANT,
      INFO,
      DEBUG,
      DEBUG_VERBOSE,
    };

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

    bool shouldLog(Level level);
    void log(PGM_P str);
    void log(PGM_P str, uint8_t val);
    void log(PGM_P str, uint16_t val);
    void log(PGM_P str, const char * val);
    void log(PGM_P str, TPC::Filesystem::DirectoryEntry * entry);
  }
}

#define LOG(LEVEL, STR, ...) if (TPC::Log::shouldLog(TPC::Log::Level::LEVEL)) { \
  static const char str[] PROGMEM = STR; \
  TPC::Log::log(str,##__VA_ARGS__); \
}

#endif
