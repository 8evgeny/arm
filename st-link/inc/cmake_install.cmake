# Install script for directory: /home/evg/SOFT/Github/Arm/st-link/inc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/stlink" TYPE FILE FILES
    "/home/evg/SOFT/Github/Arm/st-link/inc/backend.h"
    "/home/evg/SOFT/Github/Arm/st-link/inc/stlink.h"
    "/home/evg/SOFT/Github/Arm/st-link/inc/stm32.h"
    "/home/evg/SOFT/Github/Arm/st-link/inc/stm32flash.h"
    "/home/evg/SOFT/Github/Arm/st-link/inc/version.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/chipid.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/commands.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/flash_loader.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/helper.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/libusb_settings.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/logging.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/md5.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/reg.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/sg.h"
    "/home/evg/SOFT/Github/Arm/st-link/src/stlink-lib/usb.h"
    )
endif()

