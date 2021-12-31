cmake_minimum_required(VERSION 3.15)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Set ARM compiler
set(TOOLS_PATH /home/evg/toolchain/gcc-arm-none-eabi-new)
set(CMAKE_C_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-g++)

project(display_Cmake)

set(CMAKE_BUILD_TYPE debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-m3 -mthumb -std=c++17 -O3 -o -rdynamic -D_GNU_SOURCE -L./libmine")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -mcpu=cortex-m3 -mthumb -D__HEAP_SIZE=0x0C00 -D__STACK_SIZE=0x0400 -mfloat-abi=soft -fno-strict-aliasing -fdata-sections -ffunction-sections")
#-xc
#-std=c99
#--target=arm-arm-none-eabi
#-mcpu=cortex-m3
#-c
#-fno-rtti
#-funsigned-char
#-fshort-enums
#-fshort-wchar

set(CMAKE_LINK_LIBRARY_FLAG "${CMAKE_LINK_LIBRARY_FLAG} -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections -ffunction-sections -fdata-sections -fno-strict-aliasing -mfloat-abi=soft -Wl,--defsym=__STACK_SIZE=0x0100 -Wl,--defsym=__HEAP_SIZE=0x0000 -mthumb -mcpu=cortex-m3 --specs=nosys.specs ")
#--specs=nano.specs
add_definitions("-std=c++17")
#message ("CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")

set (SOURCES_C
    gpio.c
    logic.c
    mt20s4.c
    rcc_delay.c
    usb.c
    var.c
    )

set (SOURCES_CPP
    src/main.cpp
    )

set (SOURCES_SPL
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src/MDR32F9Qx_iwdg.c
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src/MDR32F9Qx_port.c
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src/MDR32F9Qx_rst_clk.c
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src/MDR32F9Qx_timer.c
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src/MDR32F9Qx_usb.c
    )

set (SOURCES_USB
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src/USB_Library/MDR32F9Qx_usb_CDC.c
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src/USB_Library/MDR32F9Qx_usb_device.c
    )

set (SOURCES_DEVICE_SUPPORT
    ../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/startup/arm/system_MDR32F9Qx.c
    )

add_executable(${PROJECT_NAME}.elf ${SOURCES_CPP} ${SOURCES_CPP} ${LINKER_SCRIPT})
set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINKER_LANGUAGE CXX)

add_library(CMSIS ${SOURCES_SPL} ${SOURCES_USB} ${SOURCES_DEVICE_SUPPORT})

include_directories(
    ../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc
    ../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/startup/arm
    ../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/CoreSupport/CM3
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/inc
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/inc/USB_Library
    ../MDR1986BExx/2.0.3/Libraries/MDR32Fx/inc
    ../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src
    include
    )

target_link_libraries(${PROJECT_NAME}.elf
    ${CMSIS}
#    m
    )

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")




#include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
#include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()


#target_link_libraries(${PROJECT_NAME}
#    ${CONAN_LIBS}
#    )
