#include <avr/pgmspace.h>

#include "USBInterface/FAT.hpp"

using namespace USBInterface::FAT;

const USBInterface::FAT::Header USBInterface::FAT::header PROGMEM = {
  // Assembled from x86 code:
  //   loop:  hlt
  //          jmp short loop
  .bootCode = {0xF4, 0xEB, 0xFD},
  .vendorStr = {'S','O','T','O','N','U','N','I'},
  .bytesPerSector = BYTES_PER_SECTOR,
  .sectorsPerCluster = SECTORS_PER_CLUSTER,
  .numReservedSectors = NUM_RESERVED_SECTORS,
  .numFATs = NUM_FATS,
  .numRootDirEntries = NUM_ROOT_DIR_ENTRIES,
  .numSectors = NUM_SECTORS,
  .mediaType = 0xF8,
  .sectorsPerFat = SECTORS_PER_FAT,
  .sectorsPerTrack = 0,
  .numHeads = 0,
  .numHiddenSectors = 0
};
