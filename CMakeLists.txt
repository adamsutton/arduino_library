# ####################################################################
# Blinky exmaple
# ####################################################################

#
# Configure Arduino
#

set(ARDUINO_DEFAULT_BOARD nano)
set(ARDUINO_DEFAULT_PORT  /dev/ttyUSB0)
set(ARDUINO_SDK_PATH      /opt/arduino)

#
# Cmake definitions
#

cmake_minimum_required(VERSION 3.5)

set(DIR ${CMAKE_CURRENT_LIST_DIR})

#
# Include directories
#
include_directories(
  ${DIR}
)

#
# Files
#

set(
  APSLIB_UTIL

  ${DIR}/util/crc.c
  ${DIR}/util/b64.c
)

set(
  APSLIB_ALL

  ${APSLIB_UTIL}
)

#
# Build library
#

if ($ENV{TARGET} MATCHES "arduino")

generate_arduino_library(
  libapsarduino

  SRCS ${APSLIB_ALL}
)

endif()

if ($ENV{TARGET} MATCHES "linux")

add_library(
  libapsarduino STATIC

  ${APSLIB_UTIL}
)

endif()

#
# Build test apps
#

if ($ENV{TARGET} MATCHES "linux")

endif()
