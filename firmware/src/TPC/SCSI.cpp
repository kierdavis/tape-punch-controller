#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#include "TPC/BlockStorage.hpp"
#include "TPC/Log.hpp"
#include "TPC/SCSI.hpp"
#include "TPC/Util.hpp"

using TPC::BlockStorage::BYTES_PER_BLOCK;
using TPC::BlockStorage::NUM_BLOCKS;

static constexpr SCSI_Request_Sense_Response_t initialSenseData PROGMEM = {
  .ResponseCode = 0x70,
  .SegmentNumber = 0,
  .SenseKey = SCSI_SENSE_KEY_GOOD,
  .Reserved = false,
  .ILI = false,
  .EOM = false,
  .FileMark = false,
  .Information = {0, 0, 0, 0},
  .AdditionalLength = 0x0A,
  .CmdSpecificInformation = {0, 0, 0, 0},
  .AdditionalSenseCode = SCSI_ASENSE_NO_ADDITIONAL_INFORMATION,
  .AdditionalSenseQualifier = SCSI_ASENSEQ_NO_QUALIFIER,
  .FieldReplaceableUnitCode = 0,
  .SenseKeySpecific = {0, 0, 0}
};

static SCSI_Request_Sense_Response_t senseData = initialSenseData;

static uint8_t lastCmd = 0;

static void resetSenseData() {
  memcpy_P(&senseData, &initialSenseData, sizeof(senseData));
}

static bool error(MS_CommandBlockWrapper_t * const commandBlock, const uint8_t key, const uint8_t addCode, const uint8_t addQual) {
  LOG("[SCSI] sending error response; most recent command was 0x", lastCmd);
  LOG("[SCSI]   key: 0x", key);
  LOG("[SCSI]   ac: 0x", addCode);
  LOG("[SCSI]   aq: 0x", addQual);
  senseData.SenseKey = key;
  senseData.AdditionalSenseCode = addCode;
  senseData.AdditionalSenseQualifier = addQual;
  // DataTransferLength represents the number of bytes left to send. If we don't
  // clear it, LUFA assumes we want to temporarily stall rather than abort with
  // an error.
  commandBlock->DataTransferLength = 0;
  return false;
}

static bool ok() {
  return true;
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
    .VendorID = {'S','O','T','O','N','U','N','I'},
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
        return error(
          commandBlock,
          SCSI_SENSE_KEY_ILLEGAL_REQUEST,
          SCSI_ASENSE_INVALID_FIELD_IN_CDB,
          SCSI_ASENSEQ_NO_QUALIFIER
        );
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

  // Send response to client, filling the rest of the client's buffer with zeros.
  Endpoint_Write_PStream_LE(responsePtr, transferLength, NULL);
  Endpoint_Null_Stream(destLength - transferLength, NULL);
  Endpoint_ClearIN();
  commandBlock->DataTransferLength -= transferLength;
  return ok();
}

static bool handleRequestSense(MS_CommandBlockWrapper_t * const commandBlock) {
  // Number of bytes that the host has allocated for the response (allocation
  // length).
  const uint8_t destLength = commandBlock->SCSICommandData[4];
  // Maximum numner of bytes that we can return.
  const uint8_t srcLength = sizeof(senseData);
  // Number of bytes that we'll transfer.
  const uint8_t transferLength = TPC::Util::min(destLength, srcLength);

  // Send response to client, filling the rest of the client's buffer with zeros.
  Endpoint_Write_Stream_LE(&senseData, transferLength, NULL);
  Endpoint_Null_Stream(destLength - transferLength, NULL);
  Endpoint_ClearIN();
  commandBlock->DataTransferLength -= transferLength;
  return ok();
}

static bool handleTestUnitReady(MS_CommandBlockWrapper_t * const commandBlock) {
  // TODO: eventually this might not always be true
  commandBlock->DataTransferLength = 0;
  return ok();
}

static bool handleReadCapacity10(MS_CommandBlockWrapper_t * const commandBlock) {
  const uint32_t addrOfLastBlock = NUM_BLOCKS - 1;
  const uint32_t blockSize = BYTES_PER_BLOCK;

  uint8_t buffer[8];
  TPC::Util::toBigEndian(addrOfLastBlock, &buffer[0]);
  TPC::Util::toBigEndian(blockSize, &buffer[4]);
  Endpoint_Write_Stream_LE(buffer, 8, NULL);
  Endpoint_ClearIN();
  commandBlock->DataTransferLength -= 8;
  return ok();
}

static bool handleSendDiagnostic(MS_CommandBlockWrapper_t * const commandBlock) {
  // TODO - maybe support some of these modes?
  return error(
    commandBlock,
    SCSI_SENSE_KEY_ILLEGAL_REQUEST,
    SCSI_ASENSE_INVALID_FIELD_IN_CDB,
    SCSI_ASENSEQ_NO_QUALIFIER
  );
}

static bool handlePreventAllowMediumRemoval(MS_CommandBlockWrapper_t * const commandBlock) {
  // TODO
  commandBlock->DataTransferLength = 0;
  return ok();
}

static bool handleWrite10(MS_CommandBlockWrapper_t * const commandBlock) {
  uint32_t startAddr32;
  uint16_t numBlocks16;
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[2], &startAddr32);
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[7], &numBlocks16);
  if (startAddr32 >= NUM_BLOCKS || (startAddr32 + numBlocks16) > NUM_BLOCKS) {
    return error(
      commandBlock,
      SCSI_SENSE_KEY_ILLEGAL_REQUEST,
      SCSI_ASENSE_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE,
      SCSI_ASENSEQ_NO_QUALIFIER
    );
  }
  const uint8_t startAddr = startAddr32;
  const uint8_t numBlocks = numBlocks16;

  for (uint8_t i = 0; i < numBlocks; i++) {
    // Wait until endpoint is ready to send more daya.
    if (Endpoint_WaitUntilReady()) {
      return false;
    }

    // Receive a block.
    const uint8_t addr = startAddr + i;
    TPC::BlockStorage::receive(addr);
    commandBlock->DataTransferLength -= BYTES_PER_BLOCK;

    // Check if endpoint is full.
    if (!Endpoint_IsReadWriteAllowed()) {
      // Flush endpoint.
      Endpoint_ClearOUT();
    }
  }

  return ok();
}

static bool handleRead10(MS_CommandBlockWrapper_t * const commandBlock) {
  uint32_t startAddr32;
  uint16_t numBlocks16;
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[2], &startAddr32);
  TPC::Util::fromBigEndian(&commandBlock->SCSICommandData[7], &numBlocks16);
  if (startAddr32 >= NUM_BLOCKS || (startAddr32 + numBlocks16) > NUM_BLOCKS) {
    return error(
      commandBlock,
      SCSI_SENSE_KEY_ILLEGAL_REQUEST,
      SCSI_ASENSE_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE,
      SCSI_ASENSEQ_NO_QUALIFIER
    );
  }
  const uint8_t startAddr = startAddr32;
  const uint8_t numBlocks = numBlocks16;

  for (uint8_t i = 0; i < numBlocks; i++) {
    // Wait until endpoint is ready to accept more data.
    if (Endpoint_WaitUntilReady()) {
      return false;
    }

    // Send a block.
    const uint8_t addr = startAddr + i;
    TPC::BlockStorage::send(addr);
    commandBlock->DataTransferLength -= BYTES_PER_BLOCK;

    // Check if endpoint is full.
    if (!Endpoint_IsReadWriteAllowed()) {
      // Flush endpoint to client.
      Endpoint_ClearIN();
    }
  }

  return ok();
}

static bool handleModeSense6(MS_CommandBlockWrapper_t * const commandBlock) {
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
  const uint8_t destLength = commandBlock->SCSICommandData[4];
  // Maximum number of bytes that we can return.
  const uint8_t srcLength = sizeof(Header);
  // Number of bytes that we'll transfer.
  const uint8_t transferLength = TPC::Util::min(destLength, srcLength);

  // Send response to client, filling the rest of the client's buffer with zeros.
  Endpoint_Write_PStream_LE(&header, transferLength, NULL);
  Endpoint_Null_Stream(destLength - transferLength, NULL);
  Endpoint_ClearIN();
  commandBlock->DataTransferLength -= transferLength;
  return ok();
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

  // Send response to client, filling the rest of the client's buffer with zeros.
  Endpoint_Write_PStream_LE(&response, transferLength, NULL);
  Endpoint_Null_Stream(destLength - transferLength, NULL);
  Endpoint_ClearIN();
  commandBlock->DataTransferLength -= transferLength;
  return ok();
}

static bool handleInvalid(MS_CommandBlockWrapper_t * const commandBlock) {
  LOG("[SCSI] unrecognised command 0x", lastCmd);
  return error(
    commandBlock,
    SCSI_SENSE_KEY_ILLEGAL_REQUEST,
    SCSI_ASENSE_INVALID_COMMAND,
    SCSI_ASENSEQ_NO_QUALIFIER
  );
}

static bool handleUnimplemented(MS_CommandBlockWrapper_t * const commandBlock) {
  LOG("[SCSI] recognised but unimplemented command 0x", lastCmd);
  return error(
    commandBlock,
    SCSI_SENSE_KEY_ILLEGAL_REQUEST,
    SCSI_ASENSE_INVALID_COMMAND,
    SCSI_ASENSEQ_NO_QUALIFIER
  );
}

bool TPC::SCSI::handle(MS_CommandBlockWrapper_t * const commandBlock) {
  // Initialise sense data to "okay", but it should be overwritten in the event
  // of an error.
  resetSenseData();

  // Some commands aren't supported by LUFA.
  static constexpr uint8_t SCSI_CMD_READ_FORMAT_CAPACITIES = 0x23;

  const uint8_t cmd = commandBlock->SCSICommandData[0];
  lastCmd = cmd;
  switch (cmd) {
    case SCSI_CMD_INQUIRY: {
      return handleInquiry(commandBlock);
    }
    case SCSI_CMD_REQUEST_SENSE: {
      return handleRequestSense(commandBlock);
    }
    case SCSI_CMD_TEST_UNIT_READY: {
      return handleTestUnitReady(commandBlock);
    }
    case SCSI_CMD_READ_CAPACITY_10: {
      return handleReadCapacity10(commandBlock);
    }
    case SCSI_CMD_START_STOP_UNIT: {
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_SEND_DIAGNOSTIC: {
      return handleSendDiagnostic(commandBlock);
    }
    case SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL: {
      return handlePreventAllowMediumRemoval(commandBlock);
    }
    case SCSI_CMD_WRITE_10: {
      return handleWrite10(commandBlock);
    }
    case SCSI_CMD_READ_10: {
      return handleRead10(commandBlock);
    }
    case SCSI_CMD_WRITE_6: {
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_READ_6: {
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_VERIFY_10: {
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_MODE_SENSE_6: {
      return handleModeSense6(commandBlock);
    }
    case SCSI_CMD_MODE_SENSE_10: {
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_READ_FORMAT_CAPACITIES: {
      return handleReadFormatCapacities(commandBlock);
    }
    default: {
      return handleInvalid(commandBlock);
    }
  }

  // Unreachable.
  return false;
}
