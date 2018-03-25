#ifndef __TPC_FILESYSTEM_HPP
#define __TPC_FILESYSTEM_HPP

#include <stdint.h>

namespace TPC {
  namespace Filesystem {
    // Together these define the memory requirement.
    static constexpr uint16_t BYTES_PER_SECTOR = 512;
    static constexpr uint16_t NUM_MUTABLE_SECTORS = 28;

    static constexpr uint8_t SECTORS_PER_CLUSTER = 1;
    static constexpr uint16_t NUM_RESERVED_SECTORS = 1;
    static constexpr uint8_t NUM_FATS = 1;
    static constexpr uint16_t NUM_ROOT_DIR_ENTRIES = 32;
    static constexpr uint16_t SECTORS_PER_FAT = 1;

    static constexpr uint32_t ROOT_DIR_SIZE_BYTES = ((uint32_t) NUM_ROOT_DIR_ENTRIES) * 32;
    static constexpr uint16_t ROOT_DIR_SIZE_SECTORS = (ROOT_DIR_SIZE_BYTES + BYTES_PER_SECTOR - 1) % BYTES_PER_SECTOR;
    static constexpr uint16_t NUM_DATA_SECTORS = NUM_MUTABLE_SECTORS - SECTORS_PER_FAT*NUM_FATS - ROOT_DIR_SIZE_SECTORS;
    static constexpr uint16_t NUM_SECTORS = NUM_MUTABLE_SECTORS + 1;

    static constexpr uint16_t BYTES_PER_CLUSTER = BYTES_PER_SECTOR * SECTORS_PER_CLUSTER;

    // 0xF0 for a generic non-partitioned disk.
    // 0xF8 for a generic partitioned disk.
    static constexpr uint8_t MEDIA_TYPE = 0xF0;

    class Header {
    public:
      /* 0x003 */ char vendorStr[8];
      /* 0x00B */ uint16_t bytesPerSector;
      /* 0x00D */ uint8_t sectorsPerCluster;
      /* 0x00E */ uint16_t numReservedSectors;
      /* 0x010 */ uint8_t numFATs;
      /* 0x011 */ uint16_t numRootDirEntries;
      /* 0x013 */ uint16_t reserved1;
      /* 0x015 */ uint8_t mediaType;
      /* 0x016 */ uint16_t sectorsPerFat;
      /* 0x018 */ uint16_t sectorsPerTrack;
      /* 0x01A */ uint16_t numHeads;
      /* 0x01C */ uint32_t numHiddenSectors;
      /* 0x020 */ uint32_t numSectors;
      /* 0x024 */ uint8_t driveNumber;
      /* 0x025 */ uint8_t reserved2;
      /* 0x026 */ uint8_t extendedBootSignature;
      /* 0x027 */ uint32_t volumeID;
      /* 0x02B */ char volumeLabel[11];
      /* 0x036 */ char fsTypeStr[8];
    };
    static_assert(sizeof(Header) == (0x03e - 0x003), "Header should be 59 bytes long");

    static constexpr Header header = {
      .vendorStr = {' ',' ',' ',' ',' ',' ',' ',' '},
      .bytesPerSector = BYTES_PER_SECTOR,
      .sectorsPerCluster = SECTORS_PER_CLUSTER,
      .numReservedSectors = NUM_RESERVED_SECTORS,
      .numFATs = NUM_FATS,
      .numRootDirEntries = NUM_ROOT_DIR_ENTRIES,
      .reserved1 = 0,
      .mediaType = MEDIA_TYPE,
      .sectorsPerFat = SECTORS_PER_FAT,
      .sectorsPerTrack = 0x20,
      .numHeads = 0x40,
      .numHiddenSectors = 0,
      .numSectors = NUM_SECTORS,
      .driveNumber = 0x00, // first removable media
      .reserved2 = 0,
      .extendedBootSignature = 0x29, // a magic number
      .volumeID = 0xED5AC123,
      .volumeLabel = {'T','A','P','E',' ','P','U','N','C','H',' '},
      .fsTypeStr = {'F','A','T','1','2',' ',' ',' '},
    };

    class DirectoryEntry {
    public:
      char name[8];
      char extension[3];
      uint8_t attributes;
      uint8_t reserved;
      uint8_t createTime[5];
      uint8_t accessTime[2];
      uint16_t permissions;
      uint8_t modifiedTime[4];
      uint16_t startCluster;
      uint32_t size;
      uint8_t formatName(char * buffer, uint8_t bufferLen);
    };
    static_assert(sizeof(DirectoryEntry) == 32, "DirectoryEntry should be 32 bytes long");

    void init();
    void scanFilesystem();

    class BlockNumber {
    protected:
      uint8_t block;
      BlockNumber(uint8_t _block) : block(_block) {}
    public:
      static BlockNumber fromBlock(uint8_t n) {
        return BlockNumber(n);
      }
      static BlockNumber fromSector(uint8_t n) {
        return BlockNumber::fromBlock(n + TPC::Filesystem::NUM_RESERVED_SECTORS);
      }
      static BlockNumber fromCluster(uint8_t n) {
        return BlockNumber::fromSector(n * TPC::Filesystem::SECTORS_PER_CLUSTER);
      }
      uint8_t toBlock() const {
        return block;
      }
      uint8_t toSector() const {
        return toBlock() - TPC::Filesystem::NUM_RESERVED_SECTORS;
      }
      uint8_t toCluster() const {
        return toSector() / TPC::Filesystem::SECTORS_PER_CLUSTER;
      }
    };

    class Reader {
    public:
      Reader();
      Reader(BlockNumber blockNum);
      bool eof() const;
      const uint8_t * pointer() const;
      uint16_t usableLength() const;
      void advance(uint16_t amount);
    protected:
      BlockNumber blockNum;
      bool eofFlag;
      uint16_t offset;
    };
  }
}

#endif
