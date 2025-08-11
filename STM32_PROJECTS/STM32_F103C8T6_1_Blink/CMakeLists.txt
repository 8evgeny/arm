cmake_minimum_required(VERSION 3.10)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Set ARM compiler
set(TOOLS_PATH /home/user/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi)
#set(CMAKE_C_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-gcc)
#set(CMAKE_CXX_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-g++)
#set(CMAKE_CXX_LINKER_LAUNCHER ${TOOLS_PATH}/bin/arm-none-eabi-g++)
#set(CMAKE_OBJCOPY ${TOOLS_PATH}/bin/arm-none-eabi-objcopy)

project(STM32_F103C8T6_1_Blink C CXX ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}\
    -mcpu=cortex-m3 \
    -std=gnu11 \
    -DUSE_HAL_DRIVER \
    -DSTM32F103xB \
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
#    --specs=nano.specs \

include_directories(
    Core/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F1xx/Include
    Drivers/CMSIS/Include
    SEGGER_RTT_V852/RTT
    SEGGER_RTT_V852/Config
    )
file (GLOB SOURCES_C
    Core/Src/*.c
    Core/Startup/startup_stm32f103c8tx.s
    Drivers/STM32F1xx_HAL_Driver/Src/*.c
    SEGGER_RTT_V852/RTT/SEGGER_RTT.c
    SEGGER_RTT_V852/RTT/SEGGER_RTT_printf.c
    )


add_executable(${PROJECT_NAME}.elf
    ${SOURCES_C}
    )

set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINKER_LANGUAGE CXX)
set(LINKER_SCRIPT_FLASH "${CMAKE_SOURCE_DIR}/STM32F103C8TX_FLASH.ld")
set(LINKER_FLAGS "SHELL: \
    -T${LINKER_SCRIPT_FLASH} \
    -mcpu=cortex-m3 \
    --specs=nosys.specs \
    -Wl,--gc-sections,--print-memory-usage \
    -static \
    --specs=nano.specs \
    -mfloat-abi=soft \
    -mthumb
    -Wl,--start-group \
    -lc \
    -lm \
    -Wl,--end-group \
    ")
#-Wl,-Map="${BuildArtifactFileBaseName}.map"
#-Wl,--no-warn-rwx-segments \
target_link_options(${PROJECT_NAME}.elf PRIVATE ${LINKER_FLAGS})


#target_link_libraries(${PROJECT_NAME}.elf PUBLIC
#    )

set(HEX_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMENT "Building ${HEX_FILE} ")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${BIN_FILE} ")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
   COMMAND st-flash --reset write ${BIN_FILE} 0x8000000
   COMMENT "Write Flash ")

#add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
#   COMMAND /home/user/JLink_Linux_V852_x86_64/JLinkExe -device STM32F103C8 -if SWD -speed 1000 -autoconnect 1 -CommandFile "/home/user/WORK/Github/Arm/STM32_PROJECTS/STM32_F103C8T6_1_Blink/flash_script.jlink"
#   COMMENT "Write Flash ")

