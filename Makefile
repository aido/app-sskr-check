#*******************************************************************************
#   Ledger App
#   (c) 2024 Ledger
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

APPNAME = "Seed Tool"
APPVERSION_M = 1
APPVERSION_N = 8
APPVERSION_P = 0
APPVERSION   = "$(APPVERSION_M).$(APPVERSION_N).$(APPVERSION_P)"

APPVERSION_RC = 0
ifneq ($(APPVERSION_RC), 0)
    APPVERSION := $(APPVERSION)-rc.$(APPVERSION_RC)
endif

VARIANT_PARAM  = NONE
VARIANT_VALUES = seed_tool

CURVE_APP_LOAD_PARAMS = secp256k1
PATH_APP_LOAD_PARAMS = ""
HAVE_APPLICATION_FLAG_DERIVE_MASTER = 1

ICON_NANOS  = glyphs/seed_nanos.gif
ICON_NANOSP = glyphs/seed_nanox.gif
ICON_NANOX  = glyphs/seed_nanox.gif
ICON_STAX   = glyphs/seed_stax_32px.gif
ICON_FLEX   = glyphs/seed_flex_40px.gif

#DEFINES += HAVE_ELECTRUM

ifneq ($(TARGET_NAME), $(filter $(TARGET_NAME), TARGET_STAX TARGET_FLEX))
    $(info Using BAGL)
    ifeq ($(TARGET_NAME),TARGET_NANOS)
        DISABLE_STANDARD_USB = 1
    endif
else
    $(info Using NBGL)
    ENABLE_NBGL_KEYBOARD = 1
    ENABLE_NBGL_KEYPAD = 1
endif

DEBUG = 0

APP_SOURCE_PATH += src

include $(BOLOS_SDK)/Makefile.standard_app
