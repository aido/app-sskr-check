#*******************************************************************************
#   Ledger Blue
#   (c) 2016 Ledger
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#*******************************************************************************

ifeq ($(BOLOS_SDK),)
$(error Environment variable BOLOS_SDK is not set)
endif

include $(BOLOS_SDK)/Makefile.defines

all: default

# Main app configuration

APPNAME = "Seed Tool"
APPVERSION_M = 1
APPVERSION_N = 8
APPVERSION_P = 0
APPVERSION   = "$(APPVERSION_M).$(APPVERSION_N).$(APPVERSION_P)"

APPVERSION_RC = 0
ifneq ($(APPVERSION_RC), 0)
    APPVERSION := $(APPVERSION)-rc.$(APPVERSION_RC)
endif

APP_LOAD_PARAMS = --appFlags 0x10 $(COMMON_LOAD_PARAMS) --curve secp256k1 --path ""

ifeq ($(TARGET_NAME), TARGET_NANOS)
    ICONNAME=glyphs/seed_nanos.gif
else ifeq ($(TARGET_NAME), TARGET_STAX)
    ICONNAME=glyphs/seed_stax_32px.gif
else
    ICONNAME=glyphs/seed_nanox.gif
endif

# Build configuration

#DEFINES += APPNAME=\"$(APPNAME)\"
DEFINES += APPVERSION=\"$(APPVERSION)\"
DEFINES += LEDGER_MAJOR_VERSION=$(APPVERSION_M)
DEFINES += LEDGER_MINOR_VERSION=$(APPVERSION_N)
DEFINES += LEDGER_PATCH_VERSION=$(APPVERSION_P)
DEFINES += OS_IO_SEPROXYHAL

DEFINES += BOLOS_APP_ICON_SIZE_B=\(9+32\)
#DEFINES += HAVE_ELECTRUM
DEFINES += IO_USB_MAX_ENDPOINTS=4 IO_HID_EP_LENGTH=64
DEFINES += HAVE_SPRINTF

ifneq ($(TARGET_NAME), TARGET_STAX)
    $(info Using BAGL)
    DEFINES += HAVE_BAGL HAVE_UX_FLOW
else
    $(info Using NBGL)
    DEFINES += NBGL_KEYBOARD
    DEFINES += NBGL_KEYPAD
endif

ifeq ($(TARGET_NAME), TARGET_NANOS)
    DEFINES += IO_SEPROXYHAL_BUFFER_SIZE_B=128
else
    DEFINES += IO_SEPROXYHAL_BUFFER_SIZE_B=300
    ifneq ($(TARGET_NAME), TARGET_STAX)
        DEFINES += HAVE_GLO096
        DEFINES += BAGL_WIDTH=128 BAGL_HEIGHT=64
        DEFINES += HAVE_BAGL_ELLIPSIS # long label truncation feature
        DEFINES += HAVE_BAGL_FONT_OPEN_SANS_REGULAR_11PX
        DEFINES += HAVE_BAGL_FONT_OPEN_SANS_EXTRABOLD_11PX
        DEFINES += HAVE_BAGL_FONT_OPEN_SANS_LIGHT_16PX
        DEFINES += HAVE_KEYBOARD_UX
    endif
endif

DEBUG = 0

ifneq ($(DEBUG), 0)
    $(info DEBUG enabled)
    DEFINES += HAVE_IO_USB HAVE_USB_APDU
    SDK_SOURCE_PATH  += lib_stusb lib_stusb_impl
    DEFINES += HAVE_PRINTF
    ifeq ($(TARGET_NAME), TARGET_NANOS)
        DEFINES += PRINTF=screen_printf
    else
        DEFINES += PRINTF=mcu_usb_printf
    endif
else
    DEFINES += PRINTF\(...\)=
endif

##############
# Compiler #
##############
ifneq ($(BOLOS_ENV),)
    $(info BOLOS_ENV=$(BOLOS_ENV))
    CLANGPATH := $(BOLOS_ENV)/clang-arm-fropi/bin/
    GCCPATH := $(BOLOS_ENV)/gcc-arm-none-eabi-5_3-2016q1/bin/
else
    $(info BOLOS_ENV is not set: falling back to CLANGPATH and GCCPATH)
endif
ifeq ($(CLANGPATH),)
    $(info CLANGPATH is not set: clang will be used from PATH)
endif
ifeq ($(GCCPATH),)
    $(info GCCPATH is not set: arm-none-eabi-* will be used from PATH)
endif

CC := $(CLANGPATH)clang
CFLAGS += -Wshadow -Wformat -DAPPNAME=\"$(APPNAME)\"
AS := $(GCCPATH)arm-none-eabi-gcc
LD := $(GCCPATH)arm-none-eabi-gcc
LDLIBS += -lm -lgcc -lc


include $(BOLOS_SDK)/Makefile.glyphs

APP_SOURCE_PATH += src

ifneq ($(TARGET_NAME),TARGET_NANOS)
    ifneq ($(TARGET_NAME), TARGET_STAX)
        SDK_SOURCE_PATH  += lib_ux
    endif
endif

# Main rules

load: all
	python -m ledgerblue.loadApp $(APP_LOAD_PARAMS)

delete:
	python -m ledgerblue.deleteApp $(COMMON_DELETE_PARAMS)

# Import generic rules from the SDK

include $(BOLOS_SDK)/Makefile.rules


listvariants:
	@echo VARIANTS APP seed_tool
