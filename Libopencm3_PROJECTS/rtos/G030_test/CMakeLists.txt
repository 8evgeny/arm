SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.7)

# Set ARM compiler
set(TOOLS_PATH /home/user/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi)
#set(CMAKE_C_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-gcc)
#set(CMAKE_CXX_COMPILER ${TOOLS_PATH}/bin/arm-none-eabi-g++)
#set(CMAKE_CXX_LINKER_LAUNCHER ${TOOLS_PATH}/bin/arm-none-eabi-g++)
#set(CMAKE_OBJCOPY ${TOOLS_PATH}/bin/arm-none-eabi-objcopy)

SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32G030F6PX_FLASH.ld)


set(COMMON_FLAGS "${CMAKE_C_FLAGS}\
    -mcpu=cortex-m0plus \
    -std=gnu11 \
    -DUSE_HAL_DRIVER \
    -DUSE_FULL_LL_DRIVER \
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

SET(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu99")

SET(CMAKE_EXE_LINKER_FLAGS_INIT " \
    -Wl,-gc-sections,--print-memory-usage \
    -T ${LINKER_SCRIPT} \
    ")

PROJECT(G030_test C CXX ASM)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-DSTM32G0)

file(GLOB_RECURSE SOURCES
    main.c
    rtos/heap_4.c
    rtos/list.c
    rtos/port.c
    rtos/tasks.c
    rtos/opencm3.c
    )
# rtos/queue.c

include_directories(
    ../../libopencm3/include
    rtos
    ./
)

add_executable(${PROJECT_NAME}.elf
    ${SOURCES}
    ${LINKER_SCRIPT}
    )

target_link_libraries(${PROJECT_NAME}.elf
    --static -nostartfiles
    -specs=nosys.specs
    -Wl,--start-group
    -lc
    -lgcc
    -lnosys
    -Wl,--end-group
    -L${CMAKE_SOURCE_DIR}/../../libopencm3/lib
    -lopencm3_stm32g0
    )

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMENT "Building ${HEX_FILE} ")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${BIN_FILE} ")

#add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
#   COMMAND st-flash --reset write ${BIN_FILE} 0x8000000
#   COMMENT "Write Flash ")
