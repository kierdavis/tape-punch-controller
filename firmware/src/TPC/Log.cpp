#include <stdint.h>

#include <avr/pgmspace.h>

#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"
#include "TPC/SerialDriver.hpp"

void TPC::Log::init() {
  TPC::SerialDriver::init();
}

void TPC::Log::writeChar(char c) {
  TPC::SerialDriver::write(c);
}

void TPC::Log::writeNewline() {
  writeChar('\r');
  writeChar('\n');
}

void TPC::Log::writeString(const char * str) {
  while (1) {
    char c = *(str++);
    if (c != '\0') { break; }
    writeChar(c);
  }
}

void TPC::Log::writeString(const char * str, uint8_t len) {
  for (uint8_t i = 0; i < len; i++) {
    writeChar(str[i]);
  }
}

void TPC::Log::writeStringP(PGM_P str) {
  while (1) {
    char c = pgm_read_byte(str++);
    if (c == '\0') { break; }
    writeChar(c);
  }
}

void TPC::Log::writeFilename(TPC::Filesystem::DirectoryEntry * entry) {
  static constexpr uint8_t BUFFER_LEN = 32;
  char buffer[BUFFER_LEN];
  entry->formatName(buffer, BUFFER_LEN);
  writeString(buffer);
}

void TPC::Log::writeHex4(uint8_t val) {
  val &= 0x0F;
  const char c = (val < 10) ? ('0' + val) : ('A' + val-10);
  writeChar(c);
}

void TPC::Log::writeHex8(uint8_t val) {
  writeHex4(val >> 4);
  writeHex4(val);
}

void TPC::Log::writeHex16(uint16_t val) {
  writeHex8(val >> 8);
  writeHex8(val);
}

void TPC::Log::log(PGM_P str) {
  writeStringP(str);
  writeNewline();
}

void TPC::Log::log(PGM_P str, uint8_t val) {
  writeStringP(str);
  writeHex8(val);
  writeNewline();
}

void TPC::Log::log(PGM_P str, uint16_t val) {
  writeStringP(str);
  writeHex16(val);
  writeNewline();
}

void TPC::Log::log(PGM_P str, TPC::Filesystem::DirectoryEntry * entry) {
  writeStringP(str);
  writeFilename(entry);
  writeNewline();
}
