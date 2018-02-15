#include <stdint.h>

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#include "USBInterface/FAT.hpp"

using namespace USBInterface::FAT;

static uint8_t mutableSectors[NUM_MUTABLE_SECTORS][BYTES_PER_SECTOR];

static void sendBootSector() {
  static const struct {
    uint8_t bootCode[3];
    char vendorStr[8];
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t numReservedSectors;
    uint8_t numFATs;
    uint16_t numRootDirEntries;
    uint16_t numSectors;
    uint8_t mediaType;
    uint16_t sectorsPerFat;
    uint16_t sectorsPerTrack;
    uint16_t numHeads;
    uint16_t numHiddenSectors;
  } header PROGMEM = {
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
  Endpoint_Write_PStream_LE(&header, sizeof(header), NULL);
  Endpoint_Null_Stream(BYTES_PER_SECTOR - sizeof(header) - 2, NULL);
  Endpoint_Write_8(0x55);
  Endpoint_Write_8(0xAA);
}

static void sendMutableSector(const uint8_t num) {
  Endpoint_Write_Stream_LE(&mutableSectors[num][0], BYTES_PER_SECTOR, NULL);
}

static void sendNullSector() {
  Endpoint_Null_Stream(BYTES_PER_SECTOR, NULL);
}

static void receiveMutableSector(const uint8_t num) {
  Endpoint_Read_Stream_LE(&mutableSectors[num][0], BYTES_PER_SECTOR, NULL);
}

static void receiveNullSector() {
  Endpoint_Discard_Stream(BYTES_PER_SECTOR, NULL);
}

void USBInterface::FAT::sendSector(const uint8_t addr) {
  if (addr == 0) {
    sendBootSector();
    return;
  }
  const uint8_t mutAddr = addr - 1;
  if (mutAddr < NUM_MUTABLE_SECTORS) {
    sendMutableSector(mutAddr);
    return;
  }
  // Address out of range.
  sendNullSector();
}

void USBInterface::FAT::receiveSector(const uint8_t addr) {
  if (addr == 0) {
    // Boot sector is immutable.
    receiveNullSector();
    return;
  }
  const uint8_t mutAddr = addr - 1;
  if (mutAddr < NUM_MUTABLE_SECTORS) {
    receiveMutableSector(mutAddr);
    return;
  }
  // Address out of range.
  receiveNullSector();
}
