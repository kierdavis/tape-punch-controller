#include <stdint.h>

#include <LUFA/Drivers/USB/USB.h>

#include "USBInterface/BlockStorage.hpp"
#include "USBInterface/FAT.hpp"

using namespace USBInterface::BlockStorage;

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
}

static void receiveNullBlock() {
  Endpoint_Discard_Stream(BYTES_PER_BLOCK, NULL);
}

void USBInterface::BlockStorage::send(const uint8_t addr) {
  if (addr == 0) {
    sendBootBlock();
    return;
  }
  const uint8_t maddr = addr - 1;
  if (maddr < NUM_MUTABLE_BLOCKS) {
    sendMutableBlock(maddr);
    return;
  }
  // Address out of range.
  sendNullBlock();
}

void USBInterface::BlockStorage::receive(const uint8_t addr) {
  if (addr == 0) {
    // Boot sector is immutable.
    receiveNullBlock();
    return;
  }
  const uint8_t maddr = addr - 1;
  if (maddr < NUM_MUTABLE_BLOCKS) {
    receiveMutableBlock(maddr);
    return;
  }
  // Address out of range.
  receiveNullBlock();
}
