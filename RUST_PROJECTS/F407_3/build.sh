#!/bin/bash
#rm -rf target
#rm stm32f407.bin
cargo build --release
cargo objcopy --bin stm32f407 --target thumbv7m-none-eabi --release -- -O binary stm32f407.bin
