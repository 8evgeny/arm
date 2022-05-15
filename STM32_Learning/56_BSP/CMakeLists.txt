cmake_minimum_required(VERSION 3.15)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Set ARM compiler
set(TOOLS_PATH /home/evg/toolchain/gcc-arm-none-eabi-new)
#set(CMAKE_C_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-gcc)
#set(CMAKE_CXX_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-g++)
set(CMAKE_CXX_LINKER_LAUNCHER ${TOOLS_PATH}/bin/arm-none-eabi-g++)
set(CMAKE_OBJCOPY ${TOOLS_PATH}/bin/arm-none-eabi-objcopy)

project(56_BSP C CXX ASM)

#set(CMAKE_BUILD_TYPE debug)
#set(CMAKE_BUILD_TYPE release)

add_definitions (-DHAVE_STDINT_H)
add_definitions (-DSTM32F746xx)

set (patchSRC "Core/Src")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}\
    -mcpu=cortex-m7 \
    -std=gnu11 \
    -DUSE_HAL_DRIVER \
    -DSTM32H753xx \
    -Os \
    -ffunction-sections \
    -fdata-sections \
    -Wall \
    -mno-unaligned-access \
    -fstack-usage \
    -MMD \
    -MP \
    -mfpu=fpv5-d16 \
    -mfloat-abi=hard \
    -mthumb \
    -Xlinker -Map=${PROJECT_NAME}.map \
    ")
#    --specs=nano.specs \

include_directories(
    ${patchSRC}/../Inc
    ${patchSRC}
    ${patchSRC}/../Startup
    Drivers/CMSIS/Device/ST/STM32F7xx/Include
    Drivers/CMSIS/Include
    Drivers/STM32F7xx_HAL_Driver/Inc
    Drivers/STM32F7xx_HAL_Driver/Inc/Legacy
    Middlewares/Third_Party/FreeRTOS/Source/include
    Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1
    Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
    Drivers/BSP/STM32746G-Discovery
    )
file (GLOB SOURCES_C ${patchSRC}/*.c STM32H753IITX_FLASH.ld)

file (GLOB CORE_SOURCES Core/Src/*.c )
add_library(CORE ${CORE_SOURCES} )

file (GLOB STARTUP_SOURCES ${patchSRC}/../Startup/*.s )
add_library(STARTUP ${STARTUP_SOURCES} )

file (GLOB HAL_SRC Drivers/STM32F7xx_HAL_Driver/Src/*)
add_library(HAL ${HAL_SRC})

file (GLOB DISCOVERY_SRC Drivers/BSP/STM32746G-Discovery/*.c )
add_library(DISCOVERY ${DISCOVERY_SRC})

file (GLOB RTOS_SRC
    Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
    Middlewares/Third_Party/FreeRTOS/Source/*.c
    Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c
    Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    )
add_library(RTOS ${RTOS_SRC})

add_executable(${PROJECT_NAME}.elf
    ${SOURCES_C}
    )

set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINKER_LANGUAGE C)

set(LINKER_SCRIPT_FLASH "${CMAKE_SOURCE_DIR}/STM32F746NGHX_FLASH.ld")
set(LINKER_SCRIPT_RAM "${CMAKE_SOURCE_DIR}/STM32F746NGHX_RAM.ld")

set(LINKER_FLAGS "SHELL: \
    -T${LINKER_SCRIPT_FLASH} \
    -mcpu=cortex-m7 \
    --specs=nosys.specs \
    -Wl,--gc-sections \
    -static \
    --specs=nano.specs \
    -mfpu=fpv5-d16 \
    -mfloat-abi=hard \
    -mthumb
    -Wl,--start-group \
    -lc \
    -lm \
    -Wl,--end-group \
    ")
#    -T${LINKER_SCRIPT_RAM} \

target_link_options(${PROJECT_NAME}.elf PRIVATE ${LINKER_FLAGS})

target_link_libraries(${PROJECT_NAME}.elf PUBLIC
    CORE
    STARTUP
    HAL
    DISCOVERY
    RTOS
    )

set(HEX_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMENT "Building ${HEX_FILE} ")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${BIN_FILE} ")
