#!/bin/bash

mkdir bin && cd build/display &&
arm-none-eabi-ld -T /home/evg/SOFT/Github/Arm/Milandr_MCU_1986x_Standard_Peripherals_Library/CMSIS/CM3/DeviceSupport/MDR32F9Qx/startup/gcc/MDR32F9Qx.ld -o ../../bin/display.elf gpio.o logic.o mt20s4.o rcc_delay.o usb.o var.o main.o   -L../lib -lspl -ldev_support -lusb && cd ../../

