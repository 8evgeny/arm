# STM32Cube-f3-meson
Another STM32Cube-f3 repos. Optimized for Meson Build System

## differences from original STM32Cube-F3
This repo is mostly just a copy of the original 1.9.0
I added of course a `meson.build` file and made a instance of the `stm32f3xx_hal_conf.h` file.
The `stm32f3xx_hal_conf.h` enables all libs.

This is not a downside! Because the linker will strip all unused symbols and functions from the libs and will only compile if something was changed in the sources we don't have more code- or data-size and also compiles with meson in an instant.

## usage (easy)
use my example project
[STM32F3Discovery-meson-example](https://github.com/hwengineer/STM32F3Discovery-meson-example)

## usage
Use this project as a `git submodule`.

The `meson.build` file defines two variables

-   `stm32cube_srcs`
-   `stm32cube_incdirs`

use this project in your *main* Meson Project as `subdir` project
and use the variables for generating your executable

        # subdir
        subdir('STM32Cube-f3-meson')

        main = executable(
                    'main.elf',
                    [srcs, stm32cube_srcs],
                    c_args              : compilerArgs,
                    link_args           : linkArgs,
                    include_directories : [incdirs, stm32cube_incdirs] )

## License
Of course the STM32Cube Library is under its own license, all other stuff under my chosen MIT License
