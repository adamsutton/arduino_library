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
  ${ARDUINO_SDK_PATH}/hardware/arduino/avr/libraries/SPI/src
)

#
# Files
#

set(
  ARDUINO_EXTRA

  ${ARDUINO_SDK_PATH}/hardware/arduino/avr/libraries/SPI/src/SPI.cpp
)

set(
  APSLIB_UTIL

  ${DIR}/util/crc.c
  ${DIR}/util/b64.c
)

set(
  APSLIB_CORE

  ${DIR}/core/sched/sched_rr.c
  ${DIR}/core/tmr/hwtimer.c
  ${DIR}/core/tmr/swtimer.c
  ${DIR}/core/log/log.c
  ${DIR}/core/log/log_stdout.c

  # Drivers

  ${DRV_DIR}/core/tmr/hwtimer.c
  ${DRV_DIR}/core/clock.c
  ${DRV_DIR}/core/stdout.cpp
)

set(
  APSLIB_PERIPH
  
  ${DRV_DIR}/periph/shift.cpp
)

set(
  APSLIB_ALL

  ${APSLIB_UTIL}
  ${APSLIB_CORE}
  ${APSLIB_PERIPH}
)

#
# Build library
#

if ($ENV{TARGET} MATCHES "arduino")

generate_arduino_library(
  apsarduino

  SRCS ${APSLIB_ALL} ${ARDUINO_EXTRA}
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

  ${DIR}/tests/sched/sched_test.c
)

target_link_libraries(
  sched_test
  
  apsarduino
  pthread
)

add_executable(
  hwtimer_test

  ${DIR}/tests/tmr/hwtimer_test.c
)

target_link_libraries(
  hwtimer_test
  
  apsarduino
  pthread
)

add_executable(
  swtimer_test

  ${DIR}/tests/tmr/swtimer_test.c
)

target_link_libraries(
  swtimer_test
  
  apsarduino
  pthread
)

else()

generate_arduino_firmware(
  sched_test

  LIBS apsarduino
  SRCS ${DIR}/tests/sched/sched_test.c
  NO_AUTOLIBS
)

generate_arduino_firmware(
  hwtimer_test

  LIBS apsarduino
  SRCS ${DIR}/tests/tmr/hwtimer_test.c
  NO_AUTOLIBS
)

generate_arduino_firmware(
  swtimer_test

  LIBS apsarduino
  SRCS ${DIR}/tests/tmr/swtimer_test.c
  NO_AUTOLIBS
)

generate_arduino_firmware(
  shift_test

  LIBS apsarduino
  SRCS ${DIR}/tests/shift/shift_test.cpp
  NO_AUTOLIBS
)

endif()
