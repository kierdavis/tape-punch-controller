#include <stdint.h>

#include <LUFA/Drivers/USB/USB.h>

#include "TPC/BlockStorage.hpp"
#include "USBInterface/FAT.hpp"

using namespace TPC::BlockStorage;
using USBInterface::FAT::NUM_RESERVED_SECTORS;

static uint8_t mutableBlocks[NUM_MUTABLE_BLOCKS][BYTES_PER_BLOCK];

static void sendBootBlock() {
  constexpr uint16_t headerLen = sizeof(USBInterface::FAT::header);
  Endpoint_Write_PStream_LE(&USBInterface::FAT::header, headerLen, NULL);
  Endpoint_Null_Stream(BYTES_PER_BLOCK - headerLen - 2, NULL);
  Endpoint_Write_8(0x55);
  Endpoint_Write_8(0xAA);
}

static void sendMutableBlock(const uint8_t maddr) {
  Endpoint_Write_Stream_LE(&mutableBlocks[maddr][0], BYTES_PER_BLOCK, NULL);
}

static void sendNullBlock() {
  Endpoint_Null_Stream(BYTES_PER_BLOCK, NULL);
}

static void receiveMutableBlock(const uint8_t maddr) {
  Endpoint_Read_Stream_LE(&mutableBlocks[maddr][0], BYTES_PER_BLOCK, NULL);
  USBInterface::FAT::scanFilesystem();
}

static void receiveNullBlock() {
  Endpoint_Discard_Stream(BYTES_PER_BLOCK, NULL);
}

void TPC::BlockStorage::send(const uint8_t addr) {
  if (addr < NUM_RESERVED_SECTORS) {
    sendBootBlock();
    return;
  }
  const uint8_t maddr = addr - NUM_RESERVED_SECTORS;
  if (maddr < NUM_MUTABLE_BLOCKS) {
    sendMutableBlock(maddr);
    return;
  }
  // Address out of range.
  sendNullBlock();
}

void TPC::BlockStorage::receive(const uint8_t addr) {
  if (addr < NUM_RESERVED_SECTORS) {
    // Boot sector is immutable.
    receiveNullBlock();
    return;
  }
  const uint8_t maddr = addr - NUM_RESERVED_SECTORS;
  if (maddr < NUM_MUTABLE_BLOCKS) {
    receiveMutableBlock(maddr);
    return;
  }
  // Address out of range.
  receiveNullBlock();
}

uint8_t * TPC::BlockStorage::get(const uint8_t addr) {
  if (addr < NUM_RESERVED_SECTORS) {
    // Boot sector is immutable, and shouldn't be used by the rest of the
    // firmware anyway.
    return nullptr;
  }
  const uint8_t maddr = addr - NUM_RESERVED_SECTORS;
  if (maddr < NUM_MUTABLE_BLOCKS) {
    return &mutableBlocks[maddr][0];
  }
  // Address out of range.
  return nullptr;
}
