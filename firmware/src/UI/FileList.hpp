#ifndef __TPC_UI_FILE_LIST_HPP
#define __TPC_UI_FILE_LIST_HPP

#include "USBInterface/FAT.hpp"

namespace UI {
  namespace FileList {
    void reset();
    void add(USBInterface::FAT::DirectoryEntry * file);
    void selectNext();
    void selectPrev();
    USBInterface::FAT::DirectoryEntry * selected();
  }
}

#endif
