SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.7)

# specify cross compilers and tools
SET(CMAKE_C_COMPILER_WORKS 1)
SET(CMAKE_C_COMPILER arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER_WORKS 1)
SET(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F102C8TX_FLASH.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/stm32f103c8t6.ld)

#Uncomment for hardware floating point
#SET(FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
#add_definitions(-DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -D__FPU_PRESENT=1)

#Uncomment for software floating point
#SET(FPU_FLAGS "-mfloat-abi=soft")

SET(COMMON_FLAGS
    "-mcpu=cortex-m3 \
    ${FPU_FLAGS} \
    -mthumb \
    -mthumb-interwork \
    -ffunction-sections \
    -fdata-sections \
    -g \
    -fno-common \
    -fmessage-length=0 \
    ")

SET(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu99")

SET(CMAKE_EXE_LINKER_FLAGS_INIT " \
    -Wl,-gc-sections,--print-memory-usage \
    -T ${LINKER_SCRIPT} \
    ")

PROJECT(ips_240_240 C CXX ASM)
set(CMAKE_CXX_STANDARD 11)

#add_definitions(-DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -D__FPU_PRESENT=1)
add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB
    -DSTM32F1 #добавил
    )

file(GLOB_RECURSE SOURCES
    Core/*.*
#    Drivers/*.*
#    Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
#    Drivers/STM32F1xx_HAL_Driver/Src/*.*
#    Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/*.*
#    Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
    ST7789/*.*


    )
# rtos/queue.c

include_directories(
    Core
    Core/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F1xx/Include
    Drivers/CMSIS/Include
    Drivers/CMSIS/NN/NN_Lib_Tests/nn_test/RTE/_ARMCM3
    Drivers/CMSIS/Core_A/Include
    Drivers/CMSIS/DSP/DSP_Lib_TestSuite/Common/JTest/inc
    ST7789
#    ./libopencm3/include/libopencm3/stm32/f1
#    libopencm3/include
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
#    -L${CMAKE_SOURCE_DIR}/libopencm3/lib -lopencm3_stm32f1
    )


#set(CMAKE_EXE_LINKER_FLAGS
#    "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
