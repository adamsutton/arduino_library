# ####################################################################
# Blinky exmaple
# ####################################################################

#
# Configure Arduino
#

set(ARDUINO_DEFAULT_BOARD atmega328)
set(ARDUINO_DEFAULT_PORT  /dev/ttyUSB0)
set(ARDUINO_SDK_PATH      /opt/arduino)

#
# Cmake definitions
#

cmake_minimum_required(VERSION 3.5)

#
# Directories
#

set(DIR     ${CMAKE_CURRENT_LIST_DIR})
set(DRV_DIR ${DIR}/drv/$ENV{TARGET})

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
  APSLIB_SCHED

  ${DIR}/sched/sched_rr.c
)

set(
  APSLIB_LOG

  ${DIR}/log/log.c
  ${DIR}/log/log_stdout.c
)

set(
  APSLIB_UTIL

  ${DIR}/util/crc.c
  ${DIR}/util/b64.c
  ${DRV_DIR}/util/clock.c
  ${DRV_DIR}/util/stdout.cpp
)

set(
  APSLIB_TMR
  
  ${DIR}/tmr/hwtimer.c
  ${DRV_DIR}/tmr/hwtimer.c
  ${DIR}/tmr/swtimer.c
)

set(
  APSLIB_ALL

  ${APSLIB_SCHED}
  ${APSLIB_LOG}
  ${APSLIB_UTIL}
  ${APSLIB_TMR}
)

#
# Build library
#

if ($ENV{TARGET} MATCHES "arduino")

generate_arduino_library(
  apsarduino

  SRCS ${APSLIB_ALL}
  NO_AUTOLIBS
)

endif()

if ($ENV{TARGET} MATCHES "linux")

add_library(
  apsarduino STATIC

  ${APSLIB_ALL}
)

endif()

#
# Build test apps
#

if ($ENV{TARGET} MATCHES "linux")

add_executable(
  sched_test

  tests/sched/sched_test.c
)

target_link_libraries(
  sched_test
  
  libapsarduino
  pthread
)

add_executable(
  hwtimer_test

  tests/tmr/hwtimer_test.c
)

target_link_libraries(
  hwtimer_test
  
  libapsarduino
  pthread
)

add_executable(
  swtimer_test

  tests/tmr/swtimer_test.c
)

target_link_libraries(
  swtimer_test
  
  libapsarduino
  pthread
)

else()

generate_arduino_firmware(
  sched_test

  LIBS apsarduino
  SRCS tests/sched/sched_test.c
  NO_AUTOLIBS
)

generate_arduino_firmware(
  hwtimer_test

  LIBS apsarduino
  SRCS tests/tmr/hwtimer_test.c
  NO_AUTOLIBS
)

generate_arduino_firmware(
  swtimer_test

  LIBS apsarduino
  SRCS tests/tmr/swtimer_test.c
  NO_AUTOLIBS
)

endif()
