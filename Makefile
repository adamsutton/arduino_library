#
# Directories
#
DIR  := $(shell cd $(dir $(lastword $(MAKEFILE_LIST))); pwd)
DDIR := $(DIR)/build.debug
RDIR := $(DIR)/build.release

#
# Host or target
#

ifeq ($(TARGET),linux)
else
TARGET      := arduino
TOOLCHAIN   := $(HOME)/opt/arduino-cmake/cmake/ArduinoToolchain.cmake
CMAKE_FLAGS := -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)
endif
export TARGET

# Update dirs
DDIR := $(DDIR).$(TARGET)
RDIR := $(RDIR).$(TARGET)

#
# Build rules
#

#
# Release/Debug?
#

ifeq ($(RELEASE),1)
BDIR        := $(RDIR)
CMAKE_FLAGS := $(CMAKE_FLAGS) -DCMAKE_BUILD_TYPE=Release
else
BDIR        := $(DDIR)
CMAKE_FLAGS := $(CMAKE_FLAGS) -DCMAKE_BUILD_TYPE=Debug
endif

default: $(BDIR) all 

distclean:
	@rm -rf $(DIR)/build.*

$(BDIR) setup:
	@mkdir -p $(BDIR) && cd $(BDIR) && (cmake $(CMAKE_FLAGS) .. || cmake .. || cmake ..)

# Note: the 3 calls to cmake above are due to some issues with x-compile
#       setup, I'm sure there is a better way

all test coverage:
	make -C $(BDIR) $@
%:
	make -C $(BDIR) $@

.PHONY: setup default distclean all test coverage
