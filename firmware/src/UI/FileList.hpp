#ifndef __TPC_UI_FILE_LIST_HPP
#define __TPC_UI_FILE_LIST_HPP

#include "TPC/Filesystem.hpp"

namespace UI {
  namespace FileList {
    void reset();
    void add(TPC::Filesystem::DirectoryEntry * file);
    void selectNext();
    void selectPrev();
    TPC::Filesystem::DirectoryEntry * selected();
  }
}

#endif
