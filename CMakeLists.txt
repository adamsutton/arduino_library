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
# C/C++ definitions
#

# C and C++
set(CMAKE_Cx_FLAGS  "${CMAKE_Cx_FLAGS} -DTARGET_$ENV{TARGET}=1")

# C
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   ${CMAKE_Cx_FLAGS}")

# C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_Cx_FLAGS}")

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
  APSLIB_SCHED

  ${DIR}/sched/sched_rr.c
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

add_executable(
  sched_test

  ${APSLIB_SCHED} tests/sched/sched_test.c
)

endif()
