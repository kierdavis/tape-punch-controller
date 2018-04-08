#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#include "TPC/BlockStorage.hpp"
#include "TPC/Filesystem.hpp"
#include "TPC/Log.hpp"
#include "TPC/SCSI.hpp"
#include "TPC/Util.hpp"

using TPC::BlockStorage::BYTES_PER_BLOCK;
using TPC::BlockStorage::NUM_BLOCKS;

class SenseTriple {
public:
  uint8_t key;
  uint8_t additionalCode;
  uint8_t additionalQualifier;
  bool ok() const {
    return key == SCSI_SENSE_KEY_GOOD;
  }
};

static constexpr SenseTriple OK = {
  .key = SCSI_SENSE_KEY_GOOD,
  .additionalCode = SCSI_ASENSE_NO_ADDITIONAL_INFORMATION,
  .additionalQualifier = SCSI_ASENSEQ_NO_QUALIFIER
};

static constexpr SenseTriple INVALID_COMMAND = {
  .key = SCSI_SENSE_KEY_ILLEGAL_REQUEST,
  .additionalCode = SCSI_ASENSE_INVALID_COMMAND,
  .additionalQualifier = SCSI_ASENSEQ_NO_QUALIFIER
};

static constexpr SenseTriple INVALID_FIELD = {
  .key = SCSI_SENSE_KEY_ILLEGAL_REQUEST,
  .additionalCode = SCSI_ASENSE_INVALID_FIELD_IN_CDB,
  .additionalQualifier = SCSI_ASENSEQ_NO_QUALIFIER
};

static constexpr SenseTriple ADDRESS_OUT_OF_RANGE = {
  .key = SCSI_SENSE_KEY_ILLEGAL_REQUEST,
  .additionalCode = SCSI_ASENSE_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE,
  .additionalQualifier = SCSI_ASENSEQ_NO_QUALIFIER
};

static constexpr SenseTriple GENERIC_ABORTED_ERROR = {
  .key = SCSI_SENSE_KEY_ABORTED_COMMAND,
  .additionalCode = SCSI_ASENSE_NO_ADDITIONAL_INFORMATION,
  .additionalQualifier = SCSI_ASENSEQ_NO_QUALIFIER
};

static constexpr SCSI_Request_Sense_Response_t initialSenseData PROGMEM = {
  .ResponseCode = 0x70,
  .SegmentNumber = 0,
  .SenseKey = OK.key,
  .Reserved = false,
  .ILI = false,
  .EOM = false,
  .FileMark = false,
  .Information = {0, 0, 0, 0},
  .AdditionalLength = 0x0A,
  .CmdSpecificInformation = {0, 0, 0, 0},
  .AdditionalSenseCode = OK.additionalCode,
  .AdditionalSenseQualifier = OK.additionalQualifier,
  .FieldReplaceableUnitCode = 0,
  .SenseKeySpecific = {0, 0, 0}
};

static SCSI_Request_Sense_Response_t senseData = initialSenseData;

static void resetSenseData() {
  memcpy_P(&senseData, &initialSenseData, sizeof(senseData));
}

static bool error(MS_CommandBlockWrapper_t * const commandBlock, const SenseTriple info) {
  const uint8_t cmd = commandBlock->SCSICommandData[0];
  LOG(INFO, "[SCSI] sending error response; most recent command was 0x", cmd);
  LOG(DEBUG, "[SCSI]   key: 0x", info.key);
  LOG(DEBUG, "[SCSI]   ac: 0x", info.additionalCode);
  LOG(DEBUG, "[SCSI]   aq: 0x", info.additionalQualifier);
  senseData.SenseKey = info.key;
  senseData.AdditionalSenseCode = info.additionalCode;
  senseData.AdditionalSenseQualifier = info.additionalQualifier;
  // DataTransferLength represents the number of bytes left to send. If we don't
  // clear it, LUFA assumes we want to temporarily stall rather than abort with
  // an error.
  commandBlock->DataTransferLength = 0;
  return false;
}

static bool ok(MS_CommandBlockWrapper_t * const commandBlock) {
  if (commandBlock->DataTransferLength != 0) {
    // Fill the rest of the host's buffer with null bytes.
    Endpoint_Null_Stream(commandBlock->DataTransferLength, NULL);
    commandBlock->DataTransferLength = 0;
  }
  if (Endpoint_BytesInEndpoint()) {
    if (USB_Endpoint_SelectedEndpoint & ENDPOINT_DIR_IN) {
      Endpoint_ClearIN();
    } else {
      Endpoint_ClearOUT();
    }
  }
  return true;
}

static bool respond(MS_CommandBlockWrapper_t * const commandBlock, const SenseTriple info) {
  if (info.ok()) {
    return ok(commandBlock);
  } else {
    return error(commandBlock, info);
  }
}

static bool handleInquiry(MS_CommandBlockWrapper_t * const commandBlock) {
  static constexpr uint8_t EVPD_MASK = 1 << 0;
  static constexpr uint8_t UNIT_SERIAL_NUMBER_PAGE_CODE = 0x80;

  static const SCSI_Inquiry_Response_t standardResponse PROGMEM = {
    .DeviceType = 0x0, // block device
    .PeripheralQualifier = 0x0, // peripheral with given device type is connected
    .Reserved = 0,
    .Removable = true,
    .Version = 0x0, // does not claim conformance to any standard
    .ResponseDataFormat = 2,
    .Reserved2 = 0,
    .NormACA = false,
    .TrmTsk = false,
    .AERC = false,
    .AdditionalLength = 0x1F,
    .Reserved3 = {0, 0},
    .SoftReset = false,
    .CmdQue = false,
    .Reserved4 = 0,
    .Linked = false,
    .Sync = false,
    .WideBus16Bit = false,
    .WideBus32Bit = false,
    .RelAddr = false,
    .VendorID = {0,0,0,0,0,0,0,0},
    .ProductID = {'T','A','P','E',' ','P','U','N','C','H',0,0,0,0,0,0},
    .RevisionID = {'0','.','1',0},
  };

  typedef struct {
    unsigned deviceType : 5;
    unsigned peripheralQualifier : 3;
    uint8_t pageCode;
    uint8_t reserved;
    uint8_t pageLength;
    uint8_t serialNumber[5];
  } ATTR_PACKED UnitSerialNumberResponse;
  static const UnitSerialNumberResponse unitSerialNumberResponse PROGMEM = {
    .deviceType = 0x0,
    .peripheralQualifier = 0x0,
    .pageCode = UNIT_SERIAL_NUMBER_PAGE_CODE,
    .reserved = 0,
    .pageLength = 5,
    .serialNumber = {'D','E','V','E','L'},
  };

  PGM_VOID_P responsePtr = nullptr;
  uint16_t responseLength = 0;

  const uint8_t flags = commandBlock->SCSICommandData[1];
  if (flags & EVPD_MASK) {
    // A Vital Product Data page is requested.
    const uint8_t pageCode = commandBlock->SCSICommandData[2];
    switch (pageCode) {
      case UNIT_SERIAL_NUMBER_PAGE_CODE: {
        responsePtr = &unitSerialNumberResponse;
        responseLength = sizeof(unitSerialNumberResponse);
        break;
      }
      default: {
        // This VPD page isn't supported.
        return respond(commandBlock, INVALID_FIELD);
      }
    }
  }
  else {
    // The standard response is requested.
    responsePtr = &standardResponse;
    responseLength = sizeof(standardResponse);
  }

  // Number of bytes that the host has allocated for the response (allocation
  // length).
  uint16_t destLength;
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[3], &destLength);
  // Maximum number of bytes that we can return.
  const uint16_t srcLength = responseLength;
  // Number of bytes that we'll transfer.
  const uint16_t transferLength = TPC::Util::min(destLength, srcLength);

  // Send response to client.
  Endpoint_Write_PStream_LE(responsePtr, transferLength, NULL);
  commandBlock->DataTransferLength -= transferLength;
  return respond(commandBlock, OK);
}

static bool handleRequestSense(MS_CommandBlockWrapper_t * const commandBlock) {
  // Number of bytes that the host has allocated for the response (allocation
  // length).
  const uint8_t destLength = commandBlock->SCSICommandData[4];
  // Maximum numner of bytes that we can return.
  const uint8_t srcLength = sizeof(senseData);
  // Number of bytes that we'll transfer.
  const uint8_t transferLength = TPC::Util::min(destLength, srcLength);

  // Send response to client.
  Endpoint_Write_Stream_LE(&senseData, transferLength, NULL);
  commandBlock->DataTransferLength -= transferLength;
  return respond(commandBlock, OK);
}

static bool handleTestUnitReady(MS_CommandBlockWrapper_t * const commandBlock) {
  // We're always ready to accept data transfer commands, so just return "yes".
  return respond(commandBlock, OK);
}

static bool handleReadCapacity10(MS_CommandBlockWrapper_t * const commandBlock) {
  const uint32_t addrOfLastBlock = NUM_BLOCKS - 1;
  const uint32_t blockSize = BYTES_PER_BLOCK;

  uint8_t buffer[8];
  TPC::Util::toBigEndian(addrOfLastBlock, &buffer[0]);
  TPC::Util::toBigEndian(blockSize, &buffer[4]);
  Endpoint_Write_Stream_LE(buffer, 8, NULL);
  commandBlock->DataTransferLength -= 8;
  return respond(commandBlock, OK);
}

static bool handleStartStopUnit(MS_CommandBlockWrapper_t * const commandBlock) {
  // No operation required.
  return respond(commandBlock, OK);
}

static bool handleSendDiagnostic(MS_CommandBlockWrapper_t * const commandBlock) {
  // TODO - maybe support some of these modes?
  return respond(commandBlock, INVALID_FIELD);
}

static bool handleWrite10(MS_CommandBlockWrapper_t * const commandBlock) {
  uint32_t startAddr32;
  uint16_t numBlocks16;
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[2], &startAddr32);
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[7], &numBlocks16);
  if (startAddr32 >= NUM_BLOCKS || (startAddr32 + numBlocks16) > NUM_BLOCKS) {
    return respond(commandBlock, ADDRESS_OUT_OF_RANGE);
  }
  const uint8_t startAddr = startAddr32;
  const uint8_t numBlocks = numBlocks16;

  for (uint8_t i = 0; i < numBlocks; i++) {
    // Wait until endpoint is ready to send more daya.
    if (Endpoint_WaitUntilReady() != ENDPOINT_READYWAIT_NoError) {
      return respond(commandBlock, GENERIC_ABORTED_ERROR);
    }

    // Receive a block.
    const uint8_t addr = startAddr + i;
    TPC::BlockStorage::receive(TPC::Filesystem::BlockNumber::fromBlock(addr));
    commandBlock->DataTransferLength -= BYTES_PER_BLOCK;
  }

  return respond(commandBlock, OK);
}

static bool handleRead10(MS_CommandBlockWrapper_t * const commandBlock) {
  uint32_t startAddr32;
  uint16_t numBlocks16;
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[2], &startAddr32);
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[7], &numBlocks16);
  if (startAddr32 >= NUM_BLOCKS || (startAddr32 + numBlocks16) > NUM_BLOCKS) {
    return respond(commandBlock, ADDRESS_OUT_OF_RANGE);
  }
  const uint8_t startAddr = startAddr32;
  const uint8_t numBlocks = numBlocks16;

  for (uint8_t i = 0; i < numBlocks; i++) {
    // Wait until endpoint is ready to accept more data.
    if (Endpoint_WaitUntilReady() != ENDPOINT_READYWAIT_NoError) {
      return respond(commandBlock, GENERIC_ABORTED_ERROR);
    }

    // Send a block.
    const uint8_t addr = startAddr + i;
    TPC::BlockStorage::send(TPC::Filesystem::BlockNumber::fromBlock(addr));
    commandBlock->DataTransferLength -= BYTES_PER_BLOCK;
  }

  return respond(commandBlock, OK);
}

static bool handleModeSense(MS_CommandBlockWrapper_t * const commandBlock, const uint16_t allocationLength) {
  typedef struct {
    uint8_t dataLength; // Length of the response, not including this byte.
    uint8_t mediumType;
    uint8_t reserved;
    uint8_t blockDescriptorLength;
  } Header;

  static const Header header PROGMEM = {
    .dataLength = 3,
    .mediumType = 0,
    .reserved = 0,
    .blockDescriptorLength = 0,
  };

  // Number of bytes that the host has allocated for the response (allocation
  // length).
  const uint16_t destLength = allocationLength;
  // Maximum number of bytes that we can return.
  const uint16_t srcLength = sizeof(Header);
  // Number of bytes that we'll transfer.
  const uint16_t transferLength = TPC::Util::min(destLength, srcLength);

  // Send response to client.
  Endpoint_Write_PStream_LE(&header, transferLength, NULL);
  commandBlock->DataTransferLength -= transferLength;
  return respond(commandBlock, OK);
}

static bool handleModeSense6(MS_CommandBlockWrapper_t * const commandBlock) {
  const uint16_t allocationLength = commandBlock->SCSICommandData[4];
  return handleModeSense(commandBlock, allocationLength);
}

static bool handleModeSense10(MS_CommandBlockWrapper_t * const commandBlock) {
  uint16_t allocationLength;
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[7], &allocationLength);
  return handleModeSense(commandBlock, allocationLength);
}

static bool handleReadFormatCapacities(MS_CommandBlockWrapper_t * const commandBlock) {
  // http://www.usb.org/developers/docs/devclass_docs/usbmass-ufi10.pdf section 4.10.

  static constexpr uint32_t NUM_BLOCKS = TPC::BlockStorage::NUM_BLOCKS;
  static constexpr uint32_t BYTES_PER_BLOCK = TPC::BlockStorage::BYTES_PER_BLOCK;
  static const struct {
    struct {
      uint8_t reserved[3];
      uint8_t capacityListLength;
    } capacityListHeader;
    struct {
      uint8_t numBlocks[4]; // A 32-bit big-endian number.
      uint8_t descriptorCode;
      uint8_t blockLength[3]; // A 24-bit big-endian number.
    } currentCapacityHeader;
  } response PROGMEM = {
    .capacityListHeader = {
      .reserved = {0, 0, 0},
      .capacityListLength = 8,
    },
    .currentCapacityHeader = {
      .numBlocks = {
        (NUM_BLOCKS >> 24) & 0xFF,
        (NUM_BLOCKS >> 16) & 0xFF,
        (NUM_BLOCKS >> 8) & 0xFF,
        NUM_BLOCKS & 0xFF,
      },
      .descriptorCode = 0x02, // formatted media
      .blockLength = {
        (BYTES_PER_BLOCK >> 16) & 0xFF,
        (BYTES_PER_BLOCK >> 8) & 0xFF,
        BYTES_PER_BLOCK & 0xFF,
      },
    },
  };

  // Number of bytes that the host has allocated for the response (allocation
  // length).
  uint16_t destLength;
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[7], &destLength);
  // Maximum number of bytes that we can return.
  const uint16_t srcLength = sizeof(response);
  // Number of bytes that we'll transfer.
  const uint16_t transferLength = TPC::Util::min(destLength, srcLength);

  // Send response to client.
  Endpoint_Write_PStream_LE(&response, transferLength, NULL);
  commandBlock->DataTransferLength -= transferLength;
  return respond(commandBlock, OK);
}

static bool handleInvalid(MS_CommandBlockWrapper_t * const commandBlock) {
  const uint8_t cmd = commandBlock->SCSICommandData[0];
  LOG(INFO, "[SCSI] unrecognised command 0x", cmd);
  return respond(commandBlock, INVALID_COMMAND);
}

static bool handleUnimplemented(MS_CommandBlockWrapper_t * const commandBlock) {
  const uint8_t cmd = commandBlock->SCSICommandData[0];
  LOG(INFO, "[SCSI] recognised but unimplemented command 0x", cmd);
  return respond(commandBlock, INVALID_COMMAND);
}

bool TPC::SCSI::handle(MS_CommandBlockWrapper_t * const commandBlock) {
  // Initialise sense data to "okay", but it should be overwritten in the event
  // of an error.
  resetSenseData();

  // Some commands aren't supported by LUFA.
  static constexpr uint8_t SCSI_CMD_READ_FORMAT_CAPACITIES = 0x23;

  const uint8_t cmd = commandBlock->SCSICommandData[0];
  switch (cmd) {
    case SCSI_CMD_INQUIRY: {
      LOG(DEBUG_VERBOSE, "[SCSI] inquiry");
      return handleInquiry(commandBlock);
    }
    case SCSI_CMD_REQUEST_SENSE: {
      LOG(DEBUG_VERBOSE, "[SCSI] request sense");
      return handleRequestSense(commandBlock);
    }
    case SCSI_CMD_TEST_UNIT_READY: {
      LOG(DEBUG_VERBOSE, "[SCSI] test unit ready");
      return handleTestUnitReady(commandBlock);
    }
    case SCSI_CMD_READ_CAPACITY_10: {
      LOG(DEBUG_VERBOSE, "[SCSI] read capacity(10)");
      return handleReadCapacity10(commandBlock);
    }
    case SCSI_CMD_START_STOP_UNIT: {
      LOG(DEBUG_VERBOSE, "[SCSI] start/stop unit");
      return handleStartStopUnit(commandBlock);
    }
    case SCSI_CMD_SEND_DIAGNOSTIC: {
      LOG(DEBUG_VERBOSE, "[SCSI] send diagnostic");
      return handleSendDiagnostic(commandBlock);
    }
    case SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL: {
      LOG(DEBUG_VERBOSE, "[SCSI] prevent/allow medium removal");
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_WRITE_10: {
      LOG(DEBUG_VERBOSE, "[SCSI] write(10)");
      return handleWrite10(commandBlock);
    }
    case SCSI_CMD_READ_10: {
      LOG(DEBUG_VERBOSE, "[SCSI] read(10)");
      return handleRead10(commandBlock);
    }
    case SCSI_CMD_WRITE_6: {
      LOG(DEBUG_VERBOSE, "[SCSI] write(6)");
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_READ_6: {
      LOG(DEBUG_VERBOSE, "[SCSI] read(6)");
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_VERIFY_10: {
      LOG(DEBUG_VERBOSE, "[SCSI] verify(10)");
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_MODE_SENSE_6: {
      LOG(DEBUG_VERBOSE, "[SCSI] mode sense(6)");
      return handleModeSense6(commandBlock);
    }
    case SCSI_CMD_MODE_SENSE_10: {
      LOG(DEBUG_VERBOSE, "[SCSI] mode sense(10)");
      return handleModeSense10(commandBlock);
    }
    case SCSI_CMD_READ_FORMAT_CAPACITIES: {
      LOG(DEBUG_VERBOSE, "[SCSI] read format capacities");
      return handleReadFormatCapacities(commandBlock);
    }
    default: {
      return handleInvalid(commandBlock);
    }
  }

  // Unreachable.
  return false;
}
