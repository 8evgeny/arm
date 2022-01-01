//Подключаем стандартные библиотеки в стиле QML
//Основные концепции языка:
//Проект (Project), Продукт (Product), Артефакт (Artifact), Модуль (Module), Правило (Rule), Группа(Group), Зависимость (Depends), Тег (Tag).
//Продукт — это аналог pro или vcproj, т. е. одна цель для сборки.
//Проект — это набор ваших продуктов вместе с зависимостями, воспринимаемый системой сборки как одно целое. Один проект — один граф сборки.
//Тег — система классификации файлов. Например «*.cpp» => «cpp»
//Правило — Преобразование файлов проекта, отмеченных определенными тегами. Генерирует другие файлы, называемые Артефактами.
//Как правило, это компиляторы или другие системы сборки.
//Артефакт — файл, над который является выходным для правила (и возможно, входным для други правил). Это обычно «obj», «exe» файлы.
//У многих QML-объектов есть свойство condition, которое отвечает за то, будет собираться он или нет. А если нам необходимо разделить так файлы?
//Для этого их можно объединить в группу (Group)
//Rule умеет срабатывать на каждый файл, попадающий под что-то. Может срабатывать по разу на каждый фаил (например, для вызова компилятора), а может один раз на все (линкер).
//Transformer предназначен для срабатывания только на один фаил, с заранее определенным именем. Например, прошивальщик или какой-нибудь хитрый скрипт.
//флаг multiplex, который говорит о том, что это правило обрабатывает сразу все файлы данного типа скопом.

// We connect standard libraries in style QML
// Basic concepts of the language:
// Project, Product, Artifact, Module, Rule, Group, Depends, Tag.
// The product is an analog of pro or vcproj, that is, one target for the assembly.
// The project is a set of your products together with dependencies, perceived by the build system as one. One project - one assembly graph.
// Tag - file classification system. For example, "* .cpp" => "cpp"
// Rule - Converting project files marked with certain tags. Generates other files called Artifacts.
// Typically, these are compilers or other build systems.
// Artifact is the file over which is the output for the rule (and possibly the input for other rules). These are usually "obj", "exe" files.
// Many QML objects have a condition property, which is responsible for whether it will be assembled or not. And if we need to split the files like this?
// To do this, you can group them into a group (Group)
// Rule is able to work on every file that falls under something. It can trigger once per each file (for example, to call the compiler), but can once on all (linker).
// Transformer is intended for triggering only one file, with a predefined name. For example, the broacher or some cunning script.
// the multiplex flag, which says that this rule processes all files of this type at once.

import qbs
import qbs.FileInfo
import qbs.ModUtils

CppApplication {

    // основной элемент файла - проект.

    //    moduleSearchPaths: "qbs" // Папка для поиска дополнительных модулей, таких как cpp и qt

    // Один проект может состоять из нескольких продуктов - конечных целей сборки.
    // Один проект может состоять из нескольких продуктов - конечных целей сборки.
    // указываем связанные файлы с помощью references. Внимание: это не жестко заданный порядок!
    // Порядок задается с помощью зависимостей, о них позже
    //    references: [
    //           "*.qbs",
    //       ]

    // the main element of the file is the project.

    // moduleSearchPaths: "qbs" // Folder for finding additional modules, such as cpp and qt

    // One project can consist of several products - the final assembly goals.
    // One project can consist of several products - the final assembly goals.
    // specify the related files with references. Attention: this is not a rigidly prescribed order!
    // The order is specified using dependencies, about them later
    // references: [
    // "* .qbs",
    //]


    name: "QT-STM32746G-Discovery"
    // Название выходного файла (без суффикса, он зависит от цели)
    // The name of the output file (without the suffix, it depends on the purpose)
    type: [
        "application",
        "bin",
        "hex",
        // Тип - приложение, т.е. исполняемый файл.
        // Type - application, i.e. executable file.
    ]

    Depends {
        name: "cpp"
        // Этот продукт зависит от компилятора C++
        // This product depends on the C ++ compiler
    }

    consoleApplication: true
    cpp.positionIndependentCode: false
    cpp.executableSuffix: ".elf"

    property string Home: path + "/.."
    property string Config: Home + "/Config"
    property string FreeRTOS: Home + "/Middlewares/Third_Party/FreeRTOS"
    property string CMSIS_RTOS: FreeRTOS + "/Source/CMSIS_RTOS"
    property string FatFs: Home + "/Middlewares/Third_Party/FatFs"
    property string HAL: Home + "/Drivers/STM32F7xx_HAL_Driver"
    property string CMSIS: Home + "/Drivers/CMSIS"
    property string Inc: Home + "/Core/Inc"
    property string Src: Home + "/Core/Src"
    property string startup: Home + "/startup"
    property string USB_HOST: Home + "/Middlewares/ST/STM32_USB_Host_Library"
    property string STemWin: Home + "/Gui"
    property string GUIBuilder: Home + "/GUIBuilder"
    property string BSP: Home + "/Drivers/BSP/STM32746G-Discovery"
    property string Utilities: Home + "/Utilities"
    property string Components: Home + "/Drivers/BSP/Components"
    property string Modules: Home + "/Modules"
    property string lwip: Home + "/Middlewares/Third_Party/LwIP"

    Group {
        // Имя группы
        // A group name
        name: "Template"
        // Список файлов в данном проекте.
        // List of files in this project.
        files: [
        ]
        // Каталоги с включенными файлами
        // Directories with included files
        cpp.includePaths: [
        ]
        // Пути до библиотек
        // Paths to Libraries
        cpp.libraryPaths: []
    }

    Group {
        //Имя группы
        name: "lwip"
        //Список файлов в данном проекте.
        files: [
            lwip + "/src/include/*/*.h",
            lwip + "/src/include/*/*/*.h",
            lwip + "/src/netif/*.c",
            lwip + "/system/*.h",
            lwip + "/system/OS/*.h",
            lwip + "/src/api/*.c",
            lwip + "/src/core/*.c",
            lwip + "/src/api/*.c",
            lwip + "/src/core/ipv4/*.c",
            lwip + "/system/OS/*.c",
        ]
    }

    Group {
        name: "Modules"
        files: [
            Modules + "/vnc_server/*.c",
            Modules + "/vnc_server/*.h",
            Modules + "/videoplayer/*.h",
            Modules + "/videoplayer/*.c",
            Modules + "/Common/*.c",
            Modules + "/Common/*.h",
            Modules + "/audio_recorder/*.c",
            Modules + "/audio_recorder/*.h",
            Modules + "/audio_player/*.c",
            Modules + "/audio_player/*.h",
            Modules + "/audio_player/Addons/SpiritDSP_LoudnessControl/*.h",
            Modules + "/audio_player/Addons/SpiritDSP_LoudnessControl/*.a",
            Modules + "/audio_player/Addons/SpiritDSP_Equalizer/*.a",
            Modules + "/audio_player/Addons/SpiritDSP_Equalizer/*.h",
            Modules + "/audio_player/Addons/SpiritDSP_Mixer/*.h",
        ]
    }

    Group {
        name: "Components"
        files: [
            Components + "/ft5336/*.c",
            Components + "/ft5336/*.h",
            Components + "/wm8994/*.c",
            Components + "/wm8994/*.h",
        ]
    }

    Group {
        name: "Utilities"
        files: [
            Utilities + "/CPU/*.h",
            Utilities + "/CPU/*.c",
        ]
    }

    Group {
        name: "BSP"
        files: [
            BSP + "/*.c",
            BSP + "/*.h",
        ]
    }

    Group {
        name: "Config"
        files: [
            Config + "/*.h",
            Config + "/*.c",
        ]
    }

    Group {
        name: "STemWin"
        files: [
            STemWin + "/Core/audio_player/*win.c",
            STemWin + "/Core/audio_recorder/*win.c",
            STemWin + "/Core/games/*win.c",
            STemWin + "/Core/gardening_control/*win.c",
            STemWin + "/Core/home_alarme/*win.c",
            STemWin + "/Core/settings/*win.c",
            STemWin + "/Core/videoplayer/*win.c",
            STemWin + "/Core/vnc_server/*win.c",
            STemWin + "/Target/*.c",
            STemWin + "/Target/*.h",
            STemWin + "/STemWin_Addons/*.c",
            STemWin + "/STemWin_Addons/*.h",
            STemWin + "/STemWin_Addons/STM32746G_Discovery_STemWin_Addons_GCC.a",
            Home + "/Middlewares/ST/STemWin/inc/*.h",
            Home + "/Middlewares/ST/STemWin/OS/GUI_X_OS.c",
            Home + "/Middlewares/ST/STemWin/Lib/STemWin540_CM7_OS_GCC_ot.a",
        ]
    }

    Group {
        name: "GUIBuilder"
        files: [
            GUIBuilder + "/*.c",
        ]
    }

    Group {
        name: "FreRTOS v9.0.0"
        files: [
            FreeRTOS + "/Source/*.c",
            FreeRTOS + "/Source/include/*.h",
            FreeRTOS + "/Source/portable/GCC/ARM_CM7/r0p1/*.h",
            FreeRTOS + "/Source/portable/GCC/ARM_CM7/r0p1/*.c",
            FreeRTOS + "/Source/portable/Common/mpu_wrappers.c",
//            FreeRTOS + "/Source/portable/MemMang/heap_1.c",
//            FreeRTOS + "/Source/portable/MemMang/heap_2.c",
//            FreeRTOS + "/Source/portable/MemMang/heap_3.c",
            FreeRTOS + "/Source/portable/MemMang/heap_4.c",
//            FreeRTOS + "/Source/portable/MemMang/heap_5.c",
        ]
    }

    Group {
        name: "CMSIS_RTOS"
        files: [
            CMSIS_RTOS + "/*.c",
            CMSIS_RTOS + "/*.h",
        ]
    }

    Group {
        name: "FatFs"
        files: [
            FatFs + "/src/*.c",
            FatFs + "/src/*.h",
            FatFs + "/src/option/syscall.c",
            FatFs + "/src/option/unicode.c",
        ]
    }

    Group {
        name: "HAL"
        files: [
            HAL + "/Src/*.c",
            HAL + "/Inc/*.h",
            HAL + "/Inc/Legacy/*.h",
        ]
        excludeFiles: [
            HAL + "/Src/stm32f7xx_hal_timebase_rtc_alarm_template.c",
            HAL + "/Src/stm32f7xx_hal_timebase_rtc_wakeup_template.c",
            HAL + "/Src/stm32f7xx_hal_timebase_tim_template.c",
        ]
    }

    Group {
        name: "CMSIS"
        files: [
            CMSIS + "/Include/*.h",
            CMSIS + "/Device/ST/STM32F7xx/Source/Templates/*",
            CMSIS + "/Device/ST/STM32F7xx/Include/*.h",
        ]
        excludeFiles: [
            CMSIS + "/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.c",
        ]
    }

    Group {
        name: "Inc"
        files: [
            Inc + "/*.h",
        ]
    }

    Group {
        name: "Src"
        files: [
            Src + "/*.c",
            Src + "/*.cpp",
        ]
        cpp.libraryPaths: [
             STemWin + "/STemWin_Addons",
             Home + "/Middlewares/ST/STemWin/Lib",
        ]

        cpp.staticLibraries: [
            ":STM32746G_Discovery_STemWin_Addons_GCC.a",
            ":STemWin540_CM7_OS_GCC_ot.a",
        ]
    }

    Group {
        name: "startup"
        files: [
            startup + "/*.s",
        ]
    }

    Group {
        name: "USB HOST"
        files: [
            USB_HOST + "/Core/Src/*.c",
            USB_HOST + "/Core/Inc/*.h",
            USB_HOST + "/Class/MSC/Src/*.c",
            USB_HOST + "/Class/MSC/Inc/*.h",
        ]
        excludeFiles: [
            USB_HOST + "/Core/Src/usbh_conf_template.c",
            USB_HOST + "/Core/Inc/usbh_conf_template.h",
        ]
    }

    Group {
        // Имя группы
        // A group name
        name: "LD"
        // Список файлов в данном проекте
        // List of files in this project
        files: [
            Home + "/*.ld",
        ]
    }

    // Каталоги с включенными файлами
    // Directories with included files
    cpp.includePaths: [
        Config,

        CMSIS + "/Include",
        CMSIS + "/Device/ST/STM32F7xx/Include",

        Inc,

        FreeRTOS + "/Source/include",
        FreeRTOS + "/Source/portable/GCC/ARM_CM7/r0p1",

        CMSIS_RTOS,

        FatFs + "/src",

        HAL + "/Inc",
        HAL + "/Inc/Legacy",

        USB_HOST + "/Core/Inc",
        USB_HOST + "/Class/MSC/Inc",

        STemWin + "/Target",
        STemWin + "/STemWin_Addons",
        Home + "/Middlewares/ST/STemWin/inc",
        Home + "/Middlewares/ST/STemWin",

        Utilities + "/CPU",
        Utilities + "/Fonts",
        BSP,

        Components,

        Modules + "/vnc_server",
        Modules + "/videoplayer",
        Modules + "/Common",
        Modules + "/audio_recorder",
        Modules + "/audio_player",
        Modules + "/audio_player/Addons/SpiritDSP_LoudnessControl",
        Modules + "/audio_player/Addons/SpiritDSP_Equalizer",
        Modules + "/audio_player/Addons/SpiritDSP_Mixer",


        lwip + "/src/include",
        lwip + "/system",
        lwip + "/system/OS",

        Components + "/ft5336",
        Components + "/wm8994",

    ]

    cpp.defines: [
        "USE_HAL_DRIVER",
        "STM32F746xx",
        "USE_STM32746G_DISCOVERY",
        "__weak=__attribute__((weak))",
        "__packed=__attribute__((__packed__))",

    ]

    //    --------------------------------------------------------------------
    //    | ARM Core | Command Line Options                       | multilib |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-M0+| -mthumb -mcpu=cortex-m0plus                | armv6-m  |
    //    |Cortex-M0 | -mthumb -mcpu=cortex-m0                    |          |
    //    |Cortex-M1 | -mthumb -mcpu=cortex-m1                    |          |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -march=armv6-m                     |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-M3 | -mthumb -mcpu=cortex-m3                    | armv7-m  |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -march=armv7-m                     |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-M4 | -mthumb -mcpu=cortex-m4                    | armv7e-m |
    //    |(No FP)   |--------------------------------------------|          |
    //    |          | -mthumb -march=armv7e-m                    |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-M4 | -mthumb -mcpu=cortex-m4 -mfloat-abi=softfp | armv7e-m |
    //    |(Soft FP) | -mfpu=fpv4-sp-d16                          | /softfp  |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -march=armv7e-m -mfloat-abi=softfp |          |
    //    |          | -mfpu=fpv4-sp-d16                          |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-M4 | -mthumb -mcpu=cortex-m4 -mfloat-abi=hard   | armv7e-m |
    //    |(Hard FP) | -mfpu=fpv4-sp-d16                          | /fpu     |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -march=armv7e-m -mfloat-abi=hard   |          |
    //    |          | -mfpu=fpv4-sp-d16                          |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-M7 | -mthumb -mcpu=cortex-m7                    | armv7e-m |
    //    |(No FP)   |--------------------------------------------|          |
    //    |          | -mthumb -march=armv7e-m                    |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-M7 | -mthumb -mcpu=cortex-m7 -mfloat-abi=softfp | armv7e-m |
    //    |(Soft FP) | -mfpu=fpv5-sp-d16                          | /softfp  |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -march=armv7e-m -mfloat-abi=softfp |          |
    //    |          | -mfpu=fpv5-sp-d16                          |          |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -mcpu=cortex-m7 -mfloat-abi=softfp |          |
    //    |          | -mfpu=fpv5-d16                             |          |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -march=armv7e-m -mfloat-abi=softfp |          |
    //    |          | -mfpu=fpv5-d16                             |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-M7 | -mthumb -mcpu=cortex-m7 -mfloat-abi=hard   | armv7e-m |
    //    |(Hard FP) | -mfpu=fpv5-sp-d16                          | /fpu     |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -march=armv7e-m -mfloat-abi=hard   |          |
    //    |          | -mfpu=fpv5-sp-d16                          |          |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -mcpu=cortex-m7 -mfloat-abi=hard   |          |
    //    |          | -mfpu=fpv5-d16                             |          |
    //    |          |--------------------------------------------|          |
    //    |          | -mthumb -march=armv7e-m -mfloat-abi=hard   |          |
    //    |          | -mfpu=fpv5-d16                             |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-R4 | [-mthumb] -march=armv7-r                   | armv7-ar |
    //    |Cortex-R5 |                                            | /thumb   |
    //    |Cortex-R7 |                                            |          |
    //    |(No FP)   |                                            |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-R4 | [-mthumb] -march=armv7-r -mfloat-abi=softfp| armv7-ar |
    //    |Cortex-R5 | -mfpu=vfpv3-d16                            | /thumb   |
    //    |Cortex-R7 |                                            | /softfp  |
    //    |(Soft FP) |                                            |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-R4 | [-mthumb] -march=armv7-r -mfloat-abi=hard  | armv7-ar |
    //    |Cortex-R5 | -mfpu=vfpv3-d16                            | /thumb   |
    //    |Cortex-R7 |                                            | /fpu     |
    //    |(Hard FP) |                                            |          |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-A* | [-mthumb] -march=armv7-a                   | armv7-ar |
    //    |(No FP)   |                                            | /thumb   |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-A* | [-mthumb] -march=armv7-a -mfloat-abi=softfp| armv7-ar |
    //    |(Soft FP) | -mfpu=vfpv3-d16                            | /thumb   |
    //    |          |                                            | /softfp  |
    //    |----------|--------------------------------------------|----------|
    //    |Cortex-A* | [-mthumb] -march=armv7-a -mfloat-abi=hard  | armv7-ar |
    //    |(Hard FP) | -mfpu=vfpv3-d16                            | /thumb   |
    //    |          |                                            | /fpu     |
    //    --------------------------------------------------------------------

    cpp.commonCompilerFlags: [
        "-mcpu=cortex-m7",
        "-mfloat-abi=hard",
        "-mfpu=fpv5-d16",
        "-mthumb",
    ]

    cpp.driverFlags: [
        "-mcpu=cortex-m7",
        "-mfloat-abi=hard",
        "-mfpu=fpv5-d16",
        "-mthumb",
        "-Xlinker",
        "--gc-sections",
        "-specs=nosys.specs",
        "-specs=nano.specs",
        "-Wl,-Map=" + path + "/../QT-STM32746G-Discovery.map",
    ]

    cpp.linkerFlags: [
        "--start-group",
        "-T" + path + "/../STM32F746NGHx_FLASH.ld",
    ]

    cpp.libraryPaths: [
        Home + "/Middlewares/ST/STemWin/Lib",
        STemWin + "/STemWin_Addons",
    ]

    cpp.staticLibraries: [
        ":STemWin540_CM7_OS_GCC_ot.a",
        ":STM32746G_Discovery_STemWin_Addons_GCC.a",
    ]

    Properties {
        condition: qbs.buildVariant === "debug"
        cpp.debugInformation: true
        cpp.optimization: "none"
    }

    Properties {
        condition: qbs.buildVariant === "release"
        cpp.debugInformation: false
        cpp.optimization: "small"
        // Виды оптимизаций
        // Types of optimizations
        // "none", "fast", "small"
    }

    Properties {
        condition: cpp.debugInformation
        cpp.defines: outer.concat("DEBUG")
    }

    Group {
        // Properties for the produced executable
        // Свойства созданного исполняемого файла
        fileTagsFilter: product.type
        qbs.install: true
    }

    // Создать .bin файл
    // Create a .bin file
    Rule {
        id: binDebugFrmw
        condition: qbs.buildVariant === "debug"
        inputs: ["application"]

        Artifact {
            fileTags: ["bin"]
            filePath: input.baseDir + "/" + input.baseName + ".bin"
        }

        prepare: {
            var objCopyPath = "arm-none-eabi-objcopy"
            var argsConv = ["-O", "binary", input.filePath, output.filePath]
            var cmd = new Command(objCopyPath, argsConv)
            cmd.description = "converting to BIN: " + FileInfo.fileName(
                        input.filePath) + " -> " + input.baseName + ".bin"

            // Запись в nor память по qspi
            // Write to the nor memory by qspi
            var argsFlashingQspi =
            [           "-f", "board/stm32f7discovery.cfg",
                        "-c", "init",
                        "-c", "reset init",
                        "-c", "flash write_bank 1 " + output.filePath + " 0",
                        "-c", "reset",
                        "-c", "shutdown"
            ]

            var cmdFlashQspi = new Command("openocd", argsFlashingQspi);
            cmdFlashQspi.description = "Wrtie to the NOR QSPI"

            // Запись во внутреннюю память
            // Write to the internal memory
            var argsFlashingInternalFlash =
            [           "-f", "board/stm32f7discovery.cfg",
                        "-c", "init",
                        "-c", "reset init",
                        "-c", "flash write_image erase " + input.filePath,
                        "-c", "reset",
                        "-c", "shutdown"
            ]

            var cmdFlashInternalFlash = new Command("openocd", argsFlashingInternalFlash);
            cmdFlashInternalFlash.description = "Wrtie to the internal flash"

            return [cmd, cmdFlashQspi, cmdFlashInternalFlash]
        }
    }

    // Создать .bin файл
    // Create a .bin file
    Rule {
        id: binFrmw
        condition: qbs.buildVariant === "release"
        inputs: ["application"]

        Artifact {
            fileTags: ["bin"]
            filePath: input.baseDir + "/" + input.baseName + ".bin"
        }

        prepare: {
            var objCopyPath = "arm-none-eabi-objcopy"
            var argsConv = ["-O", "binary", input.filePath, output.filePath]
            var cmd = new Command(objCopyPath, argsConv)
            cmd.description = "converting to BIN: " + FileInfo.fileName(
                        input.filePath) + " -> " + input.baseName + ".bin"

            // Запись в nor память по qspi
            // Write to the nor memory by qspi
            var argsFlashingQspi =
            [           "-f", "board/stm32f7discovery.cfg",
                        "-c", "init",
                        "-c", "reset init",
                        "-c", "flash write_bank 1 " + output.filePath + " 0",
                        "-c", "reset",
                        "-c", "shutdown"
            ]

            var cmdFlashQspi = new Command("openocd", argsFlashingQspi);
            cmdFlashQspi.description = "Wrtie to the NOR QSPI"

            // Запись во внутреннюю память
            // Write to the internal memory
            var argsFlashingInternalFlash =
            [           "-f", "board/stm32f7discovery.cfg",
                        "-c", "init",
                        "-c", "reset init",
                        "-c", "flash write_image erase " + input.filePath,
                        "-c", "reset",
                        "-c", "shutdown"
            ]

            var cmdFlashInternalFlash = new Command("openocd", argsFlashingInternalFlash);
            cmdFlashInternalFlash.description = "Wrtie to the internal flash"

            return [cmd, cmdFlashQspi, cmdFlashInternalFlash]
        }
    }

    // Создать .hex файл
    // Create a .hex file
    Rule {
        id: hexFrmw
        condition: qbs.buildVariant === "release"
        inputs: ["application"]

        Artifact {
            fileTags: ["hex"]
            filePath: input.baseDir + "/" + input.baseName + ".hex"
        }

        prepare: {
            var objCopyPath = "arm-none-eabi-objcopy"
            var argsConv = ["-O", "ihex", input.filePath, output.filePath]
            var cmd = new Command(objCopyPath, argsConv)
            cmd.description = "converting to HEX: " + FileInfo.fileName(
                        input.filePath) + " -> " + input.baseName + ".hex"

            return [cmd]
        }
    }
}
