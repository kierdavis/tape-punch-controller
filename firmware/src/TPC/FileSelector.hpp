#ifndef __TPC_FILE_SELECTOR_HPP
#define __TPC_FILE_SELECTOR_HPP

#include "TPC/Filesystem.hpp"

namespace TPC {
  namespace FileSelector {
    void reset();
    void add(TPC::Filesystem::DirectoryEntry * file);
    void selectNext();
    void selectPrev();
    TPC::Filesystem::DirectoryEntry * selected();
  }
}

#endif
