#include <stdint.h>

#include "Config.hpp"
#include "UI/FileList.hpp"
#include "USBInterface/FAT.hpp"

static USBInterface::FAT::DirectoryEntry * files[Config::MAX_NUM_FILES];
static uint8_t numFiles = 0;
static uint8_t selectedIndex = 0; // considered invalid when numFiles == 0.

void UI::FileList::reset() {
  numFiles = 0;
}

void UI::FileList::add(USBInterface::FAT::DirectoryEntry * file) {
  uint8_t _numFiles = numFiles;
  if (_numFiles < Config::MAX_NUM_FILES) {
    files[_numFiles] = file;
    numFiles = _numFiles + 1;
  }
  selectedIndex = 0;
}

void UI::FileList::selectNext() {
  uint8_t _numFiles = numFiles;
  if (_numFiles == 0) { return; }
  uint8_t _selectedIndex = selectedIndex;
  _selectedIndex++;
  if (_selectedIndex == _numFiles) {
    _selectedIndex = 0;
  }
  selectedIndex = _selectedIndex;
}

void UI::FileList::selectPrev() {
  uint8_t _numFiles = numFiles;
  if (_numFiles == 0) { return; }
  uint8_t _selectedIndex = selectedIndex;
  if (_selectedIndex == 0) {
    _selectedIndex = _numFiles;
  }
  _selectedIndex--;
  selectedIndex = _selectedIndex;
}

USBInterface::FAT::DirectoryEntry * UI::FileList::selected() {
  if (numFiles == 0) {
    return nullptr;
  } else {
    return files[selectedIndex];
  }
}
