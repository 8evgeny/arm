# STM32F3Discovery-meson-example

This is another STM32F3Discovery example Project.

It uses the STM32Cube-F3-meson repo which is optimised for the `meson build system`.

[STM32Cube-f3-meson](https://github.com/hwengineer/STM32Cube-F3-meson)



## Why another build system?
For myself: I hate using eclipse. And also I hate writing Makefiles.
So I had to find another build system to program my precious microcontrollers.

I read about the [mesonbuild](http://mesonbuild.com/) system and though that could be an interesting solution.

>Meson is an open source build system meant to be both extremely fast, and, even more importantly, as user friendly as possible.

Meson uses the so called [ninja](https://ninja-build.org/) back-end.

>Ninja is a small build system with a focus on speed. It differs from other build systems in two major respects: it is designed to have its input files generated by a higher-level build system, and it is designed to run builds as fast as possible.

Both are optimized for speed.

And also I can configure meson to use `llvm`. Which is also just a personal preference of mine.
If I got the time I will also make this script workable with an `arm-none-eabi-gcc` compiler.

## usage (short)

create the build folder, create the meson project and start compilation

      mkdir llvmbuild
      meson --cross-file=cross_file.build
      cd llvmbuild
      ninja

now connect your target and run openocd in a new terminal

      openocd -f interface/stlink-v2.cfg -f target/stm32f3x.cfg

goto your first terminal and start the `gdb` session

      arm-none-eabi-gdb -q llvmbuild/main.elf

Type the following command into the gdb console

      continue

enjoy!

## Toolchain Installation

take a look here : [Toochain.md](https://github.com/hwengineer/STM32F3Discovery-meson-example/blob/master/Toolchain.md)

### clone this repo

go to your destination folder and clone the repo in

      git clone https://github.com/hwengineer/STM32F3Discovery-meson-example.git
      cd STM32F3Discovery-meson-example
      git submodule update --init --recursive

And no use the commands above for compilation and testing.

## Errata
-   blink frequency is way below what is to be expected. Maybe a configuration problem

## License
Of course the STM32Cube Library is under its own license, all other stuff under my chosen MIT License