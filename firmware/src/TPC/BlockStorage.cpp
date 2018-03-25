#include <stdint.h>

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#include "TPC/BlockStorage.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"
#include "TPC/Scheduler.hpp"
#include "TPC/Timekeeping.hpp"

using namespace TPC::BlockStorage;
using TPC::Filesystem::BlockNumber;
using TPC::Filesystem::NUM_RESERVED_SECTORS;

static uint8_t mutableBlocks[NUM_MUTABLE_BLOCKS][BYTES_PER_BLOCK];

static void sendBootBlock() {
  static const TPC::BlockStorage::Header headerP PROGMEM = TPC::BlockStorage::header;
  static const uint8_t trailerP[2] PROGMEM = {0x55, 0xAA};
  Endpoint_Write_PStream_LE(&headerP, sizeof(headerP), NULL);
  Endpoint_Null_Stream(BYTES_PER_BLOCK - sizeof(headerP) - sizeof(trailerP), NULL);
  Endpoint_Write_PStream_LE(trailerP, sizeof(trailerP), NULL);
}

static void sendMutableBlock(const uint8_t maddr) {
  Endpoint_Write_Stream_LE(&mutableBlocks[maddr][0], BYTES_PER_BLOCK, NULL);
}

static void sendNullBlock() {
  Endpoint_Null_Stream(BYTES_PER_BLOCK, NULL);
}

static void receiveMutableBlock(const uint8_t maddr) {
  Endpoint_Read_Stream_LE(&mutableBlocks[maddr][0], BYTES_PER_BLOCK, NULL);
  // Schedule a filesystem scan for a few milliseconds into the future. This
  // reduces number of times the filesystem scan gets run when many blocks are
  // written in quick succession, since the scheduled time is pushed forward
  // every time another block is written.
  TPC::Scheduler::schedule(
    TPC::Scheduler::TaskID::SCAN_FILESYSTEM,
    TPC::Timekeeping::Interval::fromMilliseconds(10)
  );
}

static void receiveNullBlock() {
  Endpoint_Discard_Stream(BYTES_PER_BLOCK, NULL);
}

void TPC::BlockStorage::send(const BlockNumber blockNum) {
  LOG(DEBUG, "[BlockStorage] read 0x", blockNum.toBlock());
  if (blockNum.toBlock() < NUM_RESERVED_SECTORS) {
    sendBootBlock();
    return;
  }
  if (blockNum.toSector() < NUM_MUTABLE_BLOCKS) {
    sendMutableBlock(blockNum.toSector());
    return;
  }
  // Address out of range.
  sendNullBlock();
}

void TPC::BlockStorage::receive(const BlockNumber blockNum) {
  LOG(DEBUG, "[BlockStorage] write 0x", blockNum.toBlock());
  if (blockNum.toBlock() < NUM_RESERVED_SECTORS) {
    // Boot sector is immutable.
    receiveNullBlock();
    return;
  }
  if (blockNum.toSector() < NUM_MUTABLE_BLOCKS) {
    receiveMutableBlock(blockNum.toSector());
    return;
  }
  // Address out of range.
  receiveNullBlock();
}

uint8_t * TPC::BlockStorage::get(const BlockNumber blockNum) {
  if (blockNum.toBlock() < NUM_RESERVED_SECTORS) {
    // Boot sector is immutable, and shouldn't be used by the rest of the
    // firmware anyway.
    return nullptr;
  }
  if (blockNum.toSector() < NUM_MUTABLE_BLOCKS) {
    return &mutableBlocks[blockNum.toSector()][0];
  }
  // Address out of range.
  return nullptr;
}
