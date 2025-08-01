cmake_minimum_required(VERSION 3.10)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Set ARM compiler
#set(TOOLS_PATH /home/user/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi)
set(TOOLS_PATH /home/user/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi)

#set(CMAKE_C_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-gcc)
#set(CMAKE_CXX_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-g++)
#set(CMAKE_CXX_LINKER_LAUNCHER ${TOOLS_PATH}/bin/arm-none-eabi-g++)
#set(CMAKE_OBJCOPY ${TOOLS_PATH}/bin/arm-none-eabi-objcopy)

project(STM32G030F6P6TR C CXX ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}\
    -mcpu=cortex-m0plus \
    -std=gnu11 \
    -DUSE_HAL_DRIVER \
    -DSTM32G030xx \
    -c \
    -Os \
    -ffunction-sections \
    -fdata-sections \
    -Wall \
    -fstack-usage \
    --specs=nano.specs \
    -mfloat-abi=soft \
    -mthumb \
    ")
#    -fcyclomatic-complexity \

include_directories(
    Core/Inc
    Drivers/STM32G0xx_HAL_Driver/Inc
    Drivers/STM32G0xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32G0xx/Include
    Drivers/CMSIS/Include
    SEGGER_RTT_V852/RTT
    SEGGER_RTT_V852/Config
    )
file (GLOB SOURCES_C
    Core/Src/*.c
    Core/Startup/startup_stm32g030f6px.s
    Drivers/STM32G0xx_HAL_Driver/Src/*.c
    SEGGER_RTT_V852/RTT/SEGGER_RTT.c
    SEGGER_RTT_V852/RTT/SEGGER_RTT_printf.c
    )

add_executable(${PROJECT_NAME}.elf
    ${SOURCES_C}
    )

set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINKER_LANGUAGE CXX)
set(LINKER_SCRIPT_FLASH "${CMAKE_SOURCE_DIR}/STM32G030F6PX_FLASH.ld")
set(LINKER_FLAGS "SHELL: \
    -T${LINKER_SCRIPT_FLASH} \
    -mcpu=cortex-m0plus \
    --specs=nosys.specs \
    -Wl,--gc-sections \
    -static \
    --specs=nano.specs \
    -Wl,--gc-sections,--print-memory-usage \
    -mfloat-abi=soft \
    -mthumb
    -Wl,--start-group \
    -lc \
    -lm \
    -lstdc++ -lsupc++ \
    -Wl,--end-group \
    -Xlinker -Map=${PROJECT_NAME}.map \
    ")
#    -u _printf_float \
target_link_options(${PROJECT_NAME}.elf PRIVATE ${LINKER_FLAGS})

set(HEX_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMENT "Building ${HEX_FILE} ")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${BIN_FILE} ")

#add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
#   COMMAND st-flash --reset write ${BIN_FILE} 0x8000000
#   COMMENT "Write Flash ")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
   COMMAND /home/user/JLink_Linux_V852_x86_64/JLinkExe -device STM32G030F6 -if SWD -autoconnect 1 -CommandFile "/home/user/WORK/Github/Arm/STM32_NEW_PROJECTS/STM32G030F6P6TR/flash_script.jlink"
   COMMENT "Write Flash ")

#-speed 2000
