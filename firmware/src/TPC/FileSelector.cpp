#include <stdint.h>

#include "TPC/Config.hpp"
#include "TPC/FileSelector.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"

static TPC::Filesystem::DirectoryEntry * files[TPC::Config::MAX_NUM_FILES];
static uint8_t numFiles = 0;
static uint8_t selectedIndex = 0; // considered invalid when numFiles == 0.

void TPC::FileSelector::reset() {
  numFiles = 0;
}

void TPC::FileSelector::add(TPC::Filesystem::DirectoryEntry * file) {
  uint8_t _numFiles = numFiles;
  if (_numFiles < TPC::Config::MAX_NUM_FILES) {
    files[_numFiles] = file;
    numFiles = _numFiles + 1;
  }
  selectedIndex = 0;
}

void TPC::FileSelector::selectNext() {
  uint8_t _numFiles = numFiles;
  if (_numFiles == 0) { return; }
  uint8_t _selectedIndex = selectedIndex;
  _selectedIndex++;
  if (_selectedIndex == _numFiles) {
    _selectedIndex = 0;
  }
  LOG("[FileSelector] selected ", files[_selectedIndex]);
  selectedIndex = _selectedIndex;
}

void TPC::FileSelector::selectPrev() {
  uint8_t _numFiles = numFiles;
  if (_numFiles == 0) { return; }
  uint8_t _selectedIndex = selectedIndex;
  if (_selectedIndex == 0) {
    _selectedIndex = _numFiles;
  }
  _selectedIndex--;
  LOG("[FileSelector] selected ", files[_selectedIndex]);
  selectedIndex = _selectedIndex;
}

TPC::Filesystem::DirectoryEntry * TPC::FileSelector::selected() {
  if (numFiles == 0) {
    return nullptr;
  } else {
    return files[selectedIndex];
  }
}
