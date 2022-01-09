cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
  set(CMAKE_SYSTEM_NAME Generic)
  set(CMAKE_SYSTEM_PROCESSOR arm)

  set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
# Defines for Linux
  set(TOOLCHAIN_BIN_DIR "/home/evg/toolchain/gcc-arm-none-eabi-new/bin")
  set(TARGET_TRIPLET "arm-none-eabi-")
  set(TOOL_EXECUTABLE_SUFFIX "")
  set(CMAKE_C_COMPILER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}gcc${TOOL_EXECUTABLE_SUFFIX}")
  set(CMAKE_CXX_COMPILER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}g++${TOOL_EXECUTABLE_SUFFIX}")
  set(CMAKE_ASM_COMPILER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}gcc${TOOL_EXECUTABLE_SUFFIX}")
  set(CMAKE_OBJCOPY "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}objcopy${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "objcopy tool")
  set(CMAKE_OBJDUMP "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}objdump${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "objdump tool")
  set(CMAKE_SIZE "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}size${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "size tool")
  set(CMAKE_DEBUGER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}gdb${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "debuger")
  set(CMAKE_CPPFILT "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}c++filt${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "C++filt")

  # Set cmake configarations
#set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)

# Set the project name and version
project(gdmx_display VERSION 1.1 LANGUAGES C CXX ASM)

# Add specific definitions to the project
add_compile_definitions(STM32F103xB)
add_compile_definitions(USE_HAL_DRIVER)
add_compile_definitions(GV_INFOBOARD_V1)
#add_compile_definitions(DEBUG)
add_compile_definitions(RELEASE)

# Specify the C standard to the project
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Specify the C++ standard to the project
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Set C compiler flags

#-c
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
-mcpu=cortex-m3 \
-std=gnu11 \
-DGV_INFOBOARD_V1 \
-DUSE_HAL_DRIVER \
-DSTM32F103xB \
-I../Middlewares/Third_Party/FreeRTOS/Source/include \
-I../Inc \
-I../Drivers/CMSIS/Device/ST/STM32F1xx/Include \
-I../Drivers/CMSIS/Include \
-I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc \
-I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy \
-I../Drivers/STM32F1xx_HAL_Driver/Inc \
-I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
-I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc \
-I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 \
-O3 \
-ffunction-sections \
-fdata-sections \
-Wall \
-fstack-usage \
--specs=nano.specs \
-mfloat-abi=soft \
-mthumb \
")

#--specs=nosys.specs \
#-O0 \
#-Wl,-Map=${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.map"

# Set C++ compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-mcpu=cortex-m3 \
-std=gnu14 \
-DGV_INFOBOARD_V1 \
-DUSE_HAL_DRIVER \
-DSTM32F103xB \
-I../Middlewares/Third_Party/FreeRTOS/Source/include \
-I../Inc \
-I../Drivers/CMSIS/Device/ST/STM32F1xx/Include \
-I../Drivers/CMSIS/Include \
-I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc \
-I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy \
-I../Drivers/STM32F1xx_HAL_Driver/Inc \
-I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
-I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc \
-I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 \
-O3 \
-ffunction-sections \
-fdata-sections \
-fno-exceptions \
-fno-rtti \
-fno-use-cxa-atexit \
-Wall \
-fstack-usage \
--specs=nano.specs \
-mfloat-abi=soft \
-mthumb \
-c \
")

#-specs=nosys.specs \
#-O0 \
#-Wl,-Map=${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.map \

# Set linker flags
set(CMAKE_LINK_LIBRARY_FLAG "${CMAKE_LINK_LIBRARY_FLAG} \
-mcpu=cortex-m3 \
-Wl,--gc-sections \
-specs=nosys.specs \
-T\"/home/evg/STM32CubeIDE/workspace_1.7.0/gdmx-display/STM32F103C8TX_FLASH.ld\" \
-Wl,-Map=\"${ProjName}.map\" \
-Wl,--gc-sections \
-static \
-specs=nano.specs \
-mfloat-abi=soft \
-mthumb \
-Wl,--start-group \
-lc \
-lm \
-lstdc++ \
-lsupc++ \
-Wl,--end-group
")

#-T${LINKER_SCRIPT} \
#-lm \
#-lnosys \
#-lgcc \
#-lc \
#-lstdc++" CACHE INTERNAL "

set(LINKER_SCRIPT "${PROJECT_SOURCE_DIR}/STM32F103C8TX_FLASH.ld")
# Add sources to the project
set(FREERTOS_DIR Middlewares/Third_Party/FreeRTOS/Source/)
set(STM32_USB_Device_DIR Middlewares/ST/STM32_USB_Device_Library/)

file(GLOB_RECURSE USER_SOURCES "Src/*.c")
file(GLOB_RECURSE HAL_SOURCES "Drivers/STM32F1xx_HAL_Driver/Src/*.c")
file(
    GLOB_RECURSE
    FREERTOS_SOURCES
    "${FREERTOS_DIR}/*.c"
    "${FREERTOS_DIR}/CMSIS_RTOS/*.c"
    "${FREERTOS_DIR}/portable/GCC/ARM_CM3/*.c"
    "${STM32_USB_Device_DIR}/Core/Src/*.c"
    "${STM32_USB_Device_DIR}/Class/CDC/Src/*.c"
)

add_library(
    CMSIS
    Src/system_stm32f1xx.c
    Startup/startup_stm32f103c8tx.s
)

# Add includes to the project
include_directories(Inc)
include_directories(Drivers/STM32F1xx_HAL_Driver/Inc)
include_directories(Drivers/STM32F1xx_HAL_Driver/Inc/Legacy)
include_directories(Drivers/CMSIS/Include)
include_directories(Drivers/CMSIS/Device/ST/STM32F1xx/Include)

include_directories(${FREERTOS_DIR})
include_directories(${FREERTOS_DIR}/CMSIS_RTOS)
include_directories(${FREERTOS_DIR}/include)
include_directories(${FREERTOS_DIR}/portable/GCC/ARM_CM3/)
include_directories(${STM32_USB_Device_DIR}/Core/Inc/)
include_directories(${STM32_USB_Device_DIR}/Class/CDC/Inc/)

add_executable(${PROJECT_NAME}.elf ${USER_SOURCES} ${HAL_SOURCES} ${LINKER_SCRIPT} ${FREERTOS_SOURCES})

target_link_libraries(${PROJECT_NAME}.elf CMSIS)

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMENT "Building ${HEX_FILE}"
#    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
#    COMMENT "\nBuilding ${BIN_FILE}"
    )
