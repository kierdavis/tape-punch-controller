# Based on LUFA example makefile, which can be found at
# http://www.fourwalledcubicle.com/files/LUFA/Doc/151115/html/_page__configuring_apps.html

# Run "make help" for target help.

MCU = atxmega192c3
ARCH = XMEGA
F_CPU = 12000000
F_USB = 48000000
BOARD = NONE

TARGET = firmware
TARGET_SRC = $(shell find src -name '*.cpp')
SRC = $(TARGET_SRC) $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS) $(LUFA_SRC_PLATFORM)

OPTIMIZATION = s
LTO = Y
CC_FLAGS += -Isrc -Wall -Werror -DUSE_LUFA_CONFIG_HEADER
LD_FLAGS += -Wl,--defsym=__heap_end=0x805e00
CPP_STANDARD = c++14

# TODO: http://www.fourwalledcubicle.com/files/LUFA/Doc/151115/html/_page__token_summary.html

LUFA_PATH = lib/lufa/LUFA

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
