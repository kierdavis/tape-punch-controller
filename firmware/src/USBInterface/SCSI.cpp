#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

#include "Config.hpp"
#include "Peripheral/Serial.hpp"
#include "USBInterface/FAT.hpp"
#include "USBInterface/SCSI.hpp"
#include "Util/Arith.hpp"
#include "Util/Word.hpp"

using USBInterface::FAT::BYTES_PER_SECTOR;
using USBInterface::FAT::NUM_SECTORS;

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

static void resetSenseData() {
  memcpy_P(&senseData, &initialSenseData, sizeof(senseData));
}

static bool error(const uint8_t key, const uint8_t addCode, const uint8_t addQual) {
  SERIAL_WRITE(" -> error 0x");
  Peripheral::Serial::writeHex8(key);
  SERIAL_WRITE(" 0x");
  Peripheral::Serial::writeHex8(addCode);
  SERIAL_WRITE(" 0x");
  Peripheral::Serial::writeHex8(addQual);
  SERIAL_WRITE("\r\n");
  senseData.SenseKey = key;
  senseData.AdditionalSenseCode = addCode;
  senseData.AdditionalSenseQualifier = addQual;
  return false;
}

static bool ok() {
  SERIAL_WRITE(" -> ok\r\n");
  return true;
}

static bool handleInquiry(MS_CommandBlockWrapper_t * const commandBlock) {
  static const SCSI_Inquiry_Response_t response PROGMEM = {
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
    .ProductID = {'T','A','P','E',' ','P','U','N','C','H',' ','C','T','R','L',0},
    .RevisionID = {'0','.','1',0},
  };

  // Check whether the type of response requested by the client is supported.
  static constexpr uint8_t CMDDT_MASK = 1 << 1;
  static constexpr uint8_t EVPD_MASK = 1 << 0;
  const uint8_t flags = commandBlock->SCSICommandData[1];
  const uint8_t pageCode = commandBlock->SCSICommandData[2];
  if ((flags & (CMDDT_MASK | EVPD_MASK)) || (pageCode != 0)) {
    return error(
      SCSI_SENSE_KEY_ILLEGAL_REQUEST,
      SCSI_ASENSE_INVALID_FIELD_IN_CDB,
      SCSI_ASENSEQ_NO_QUALIFIER
    );
  }

  // Number of bytes that the host has allocated for the response (allocation
  // length).
  uint16_t destLength;
  Util::Word::fromBigEndian(&commandBlock->SCSICommandData[3], &destLength);
  // Maximum number of bytes that we can return.
  const uint16_t srcLength = sizeof(response);
  // Number of bytes that we'll transfer.
  const uint16_t transferLength = Util::Arith::min(destLength, srcLength);

  // Send response to client, filling the rest of the client's buffer with zeros.
  Endpoint_Write_PStream_LE(&response, transferLength, NULL);
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
  const uint8_t transferLength = Util::Arith::min(destLength, srcLength);

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
  const uint32_t addrOfLastBlock = NUM_SECTORS - 1;
  const uint32_t blockSize = BYTES_PER_SECTOR;

  uint8_t buffer[8];
  Util::Word::toBigEndian(addrOfLastBlock, &buffer[0]);
  Util::Word::toBigEndian(blockSize, &buffer[4]);
  Endpoint_Write_Stream_LE(buffer, 8, NULL);
  Endpoint_ClearIN();
  commandBlock->DataTransferLength -= 8;
  return ok();
}

static bool handleSendDiagnostic(MS_CommandBlockWrapper_t * const commandBlock) {
  // TODO - maybe support some of these modes?
  return error(
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
  Util::Word::fromBigEndian(&commandBlock->SCSICommandData[2], &startAddr32);
  Util::Word::fromBigEndian(&commandBlock->SCSICommandData[7], &numBlocks16);
  if (startAddr32 >= NUM_SECTORS || (startAddr32 + numBlocks16) > NUM_SECTORS) {
    return error(
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

    // Receive a sector.
    const uint8_t addr = startAddr + i;
    SERIAL_WRITE("\r\n[SCSI] write: 0x");
    Peripheral::Serial::writeHex8(addr);
    USBInterface::FAT::receiveSector(addr);
    commandBlock->DataTransferLength -= BYTES_PER_SECTOR;

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
  Util::Word::fromBigEndian(&commandBlock->SCSICommandData[2], &startAddr32);
  Util::Word::fromBigEndian(&commandBlock->SCSICommandData[7], &numBlocks16);
  if (startAddr32 >= NUM_SECTORS || (startAddr32 + numBlocks16) > NUM_SECTORS) {
    return error(
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

    // Send a sector.
    const uint8_t addr = startAddr + i;
    SERIAL_WRITE("\r\n[SCSI] read: 0x");
    Peripheral::Serial::writeHex8(addr);
    USBInterface::FAT::sendSector(addr);
    commandBlock->DataTransferLength -= BYTES_PER_SECTOR;

    // Check if endpoint is full.
    if (!Endpoint_IsReadWriteAllowed()) {
      // Flush endpoint to client.
      Endpoint_ClearIN();
    }
  }

  return ok();
}

static bool handleModeSense6(MS_CommandBlockWrapper_t * const commandBlock) {
  // TODO: handle this properly
  Endpoint_Null_Stream(4, NULL);
  Endpoint_ClearIN();
  commandBlock->DataTransferLength -= 4;
  return ok();
}

static bool handleInvalid(MS_CommandBlockWrapper_t * const commandBlock) {
  return error(
    SCSI_SENSE_KEY_ILLEGAL_REQUEST,
    SCSI_ASENSE_INVALID_COMMAND,
    SCSI_ASENSEQ_NO_QUALIFIER
  );
}

static bool handleUnimplemented(MS_CommandBlockWrapper_t * const commandBlock) {
  SERIAL_WRITE(" (NOT IMPLEMENTED)");
  return handleInvalid(commandBlock);
}

bool USBInterface::SCSI::handle(MS_CommandBlockWrapper_t * const commandBlock) {
  // Initialise sense data to "okay", but it should be overwritten in the event
  // of an error.
  resetSenseData();

  SERIAL_WRITE("[SCSI] command: ");

  const uint8_t cmd = commandBlock->SCSICommandData[0];
  switch (cmd) {
    case SCSI_CMD_INQUIRY: {
      SERIAL_WRITE("inquiry");
      return handleInquiry(commandBlock);
    }
    case SCSI_CMD_REQUEST_SENSE: {
      SERIAL_WRITE("request sense");
      return handleRequestSense(commandBlock);
    }
    case SCSI_CMD_TEST_UNIT_READY: {
      SERIAL_WRITE("test unit ready");
      return handleTestUnitReady(commandBlock);
    }
    case SCSI_CMD_READ_CAPACITY_10: {
      SERIAL_WRITE("read capacity 10");
      return handleReadCapacity10(commandBlock);
    }
    case SCSI_CMD_START_STOP_UNIT: {
      SERIAL_WRITE("start stop unit");
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_SEND_DIAGNOSTIC: {
      SERIAL_WRITE("send diagnostic");
      return handleSendDiagnostic(commandBlock);
    }
    case SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL: {
      SERIAL_WRITE("prevent allow medium removal");
      return handlePreventAllowMediumRemoval(commandBlock);
    }
    case SCSI_CMD_WRITE_10: {
      SERIAL_WRITE("write 10");
      return handleWrite10(commandBlock);
    }
    case SCSI_CMD_READ_10: {
      SERIAL_WRITE("read 10");
      return handleRead10(commandBlock);
    }
    case SCSI_CMD_WRITE_6: {
      SERIAL_WRITE("write 6");
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_READ_6: {
      SERIAL_WRITE("read 6");
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_VERIFY_10: {
      SERIAL_WRITE("verify 10");
      return handleUnimplemented(commandBlock);
    }
    case SCSI_CMD_MODE_SENSE_6: {
      SERIAL_WRITE("mode sense 6");
      return handleModeSense6(commandBlock);
    }
    case SCSI_CMD_MODE_SENSE_10: {
      SERIAL_WRITE("mod sense 10");
      return handleUnimplemented(commandBlock);
    }
    default: {
      SERIAL_WRITE("unknown 0x");
      Peripheral::Serial::writeHex8(cmd);
      return handleInvalid(commandBlock);
    }
  }

  // Unreachable.
  return false;
}
