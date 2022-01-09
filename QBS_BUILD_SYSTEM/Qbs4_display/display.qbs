import qbs
Project {
    name: "display"
    property string Home: path + "/.."
    property string CMSIS: Home + "/MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx"
    property string Dev_support: CMSIS + "/MDR32Fx/DeviceSupport/MDR1986VE9x"
    property string Dev_support_inc: Dev_support + "/inc"
    property string Dev_support_startup_arm: Dev_support + "/startup/arm"
    property string Dev_support_startup_gcc: Home + "/Milandr_MCU_1986x_Standard_Peripherals_Library/CMSIS/CM3/DeviceSupport/MDR32F9Qx/startup/gcc"
    property string Core_support: CMSIS + "/CoreSupport/CM3"
    property string SPL: Home + "/MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx"
    property string SPL_inc: SPL + "/inc"
    property string SPL_src: SPL + "/src"
    property string USB: SPL_inc + "/USB_Library"
    property string Startup: Home + "/Milandr_MCU_1986x_Standard_Peripherals_Library/CMSIS/CM3/DeviceSupport/MDR32F9Qx/startup/gcc"
    Product {
//CppApplication {



//        cpp.toolchainInstallPath: "/home/evg/toolchain/gcc-arm-none-eabi-new/bin"
//        cpp.cxxCompilerName: "arm-none-eabi-g++"
//        Depends {name: "c" }
        name: "milandr_display"
//        Depends {name: "cpp" }
        type: [
            "application",
            "bin",
            "hex",
            // Тип - приложение, т.е. исполняемый файл.
            // Type - application, i.e. executable file.
        ]

        Group {
            name: "sources_c"
            prefix: "src/"
            files: [
                "*.c",
                "*.h"
            ]
            fileTags: ['c']
        }
//        Group {
//            name: "includes"
////            prefix: Dev_support_inc + "/"
//            files: [
////                "MDR32Fx.h",
//   "/home/evg/SOFT/Github/Arm/MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc/MDR32Fx.h"
//            ]
//            fileTags: ['h']
//        }


        Group {
            name: "sources_cpp"
            files: [
                "src/*.cpp",
//                "src/main.cpp",
//                "/home/evg/SOFT/Github/Arm/MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc/MDR32Fx.h"
            ]
            fileTags: ['cpp']
        }
        Group {
            name: "sources_spl"
            prefix: SPL_src + "/"
            files: [
                SPL_src + "MDR32F9Qx_iwdg.c",
                "MDR32F9Qx_port.c",
                "MDR32F9Qx_rst_clk.c",
                "MDR32F9Qx_timer.c",
                "MDR32F9Qx_usb.c",
            ]
            fileTags: ['src_spl']
        }
        Group {
            name: "sources_usb"
            prefix: SPL_src + "/USB_Library/"
            files: [
                "MDR32F9Qx_usb_CDC.c",
                "MDR32F9Qx_usb_device.c",
            ]
            fileTags: ['src_usb']
        }
        Group {
            name: "sources_dev_support"
            prefix: Dev_support_startup_arm + "/"
            files: [
                "system_MDR32F9Qx.c",
            ]
            fileTags: ['src_dev_support']
        }
        Group {
            name: "startup_dev_support"
            prefix: Startup + "/"
            files: [
                "system_MDR32F9Qx.c",
            ]
            fileTags: ['src_dev_support']
        }

        cpp.debugInformation: true
        cpp.commonCompilerFlags: [
            "-mcpu=cortex-m3", "-mthumb",
//            "-mfloat-abi=hard","-mfpu=fpv4-sp-d16",
//            "-Os","-g3","-Wall","-fmessage-length=0", "-ffunction-sections","-c","-fmessage-length=0",
        ]
        cpp.includePaths: [
            Dev_support_inc,
            "../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc",
            "../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/startup/arm",
            "../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/CoreSupport/CM3",
            "../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx",
            "../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/inc",
            "../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/inc/USB_Library",
            "../MDR1986BExx/2.0.3/Libraries/MDR32Fx/inc",
            "../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src",
            "./include"
        ]
        cpp.toolchainInstallPath: "/home/evg/toolchain/gcc-arm-none-eabi-new/bin"
        cpp.cxxCompilerName: "arm-none-eabi-g++"


        Rule {
            inputs: [
                "c"
            ]
            Artifact {
                fileTags: ['obj']
                filePath: input.fileName + '.o'
            }
            prepare: {
                var args = [];
                var includes = [];
                args.push("-mcpu=cortex-m3")
                args.push("-mthumb")
                args.push("-g")
                args.push("-ffunction-sections")
                args.push("-O0")
                args.push("-Wall")
                args.push("-Wunused")
                args.push("-DM3")
                args.push('-c');
                args.push(input.filePath);
                args.push('-o');
                args.push(output.filePath);
                includes.push("../inc_spl");
//                includes.push("../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc");
//                includes.push("../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/startup/arm");
//                includes.push("../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/CoreSupport/CM3");
//                includes.push("../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx");
//                includes.push("../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/inc");
//                includes.push("../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/inc/USB_Library");
//                includes.push("../MDR1986BExx/2.0.3/Libraries/MDR32Fx/inc");
//                includes.push("../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src");
                var compilerPath = "/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-gcc";
                var cmd = new Command(compilerPath, args, includes);
                cmd.description = 'compiling ' + input.fileName;
                cmd.highlight = 'compiler';
                cmd.silent = false;
                return cmd;
            }
        }

        Rule {
            inputs: [
                "cpp"
            ]
            Artifact {
                fileTags: ['obj']
                filePath: input.fileName + '.o'
            }
            prepare: {
                var args = [];
                var includes = [];
                args.push("-mcpu=cortex-m3")
                args.push("-mthumb")
                args.push("-g")
                args.push("-ffunction-sections")
                args.push("-O0")
                args.push("-Wall")
                args.push("-Wunused")
                args.push("-DM3")
                args.push('-c');
                args.push(input.filePath);
                args.push('-o');
                args.push(output.filePath);
                includes.push("inc_spl");
                includes.push("../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc");
                includes.push("../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/startup/arm");
                includes.push("../MDR1986BExx/2.0.3/Libraries/CMSIS/MDR32Fx/CoreSupport/CM3");
                includes.push("../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx");
                includes.push("../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/inc");
                includes.push("../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/inc/USB_Library");
                includes.push("../MDR1986BExx/2.0.3/Libraries/MDR32Fx/inc");
                includes.push("../MDR1986BExx/2.0.3/Libraries/SPL/MDR32Fx/src");
                var compilerPath = "/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-g++";
                var cmd = new Command(compilerPath, args, includes);
                cmd.description = 'compiling ' + input.fileName;
                cmd.highlight = 'compiler';
                cmd.silent = false;
                return cmd;
            }
        }


        Rule{
            multiplex: true
            inputs: ['obj']
            Artifact{
                fileTags:['elf']
                filePath: project.name + '.elf'
            }
            prepare:{
                var args = []
                args.push("-mcpu=cortex-m3")
                args.push("-mthumb")
                args.push("-g")
                args.push("-nostartfiles")
                args.push("-O0")
                args.push("-Wl,--gc-sections")
                for(i in inputs['obj'])
                    args.push(inputs["obj"][i].filePath);
                args.push("-T/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-ld");
                args.push('-o');
                args.push(output.filePath);
                var compilerPath = "/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-g++";
                var cmd = new Command(compilerPath,args);
                cmd.description = "linking"+project.name
                return cmd;
            }
        }

        Rule{
            inputs: ['elf']
            Artifact{
                fileTags:['hex']
                filePath: project.name + '.hex'
            }
            prepare:{
                var args = []
                args.push("-O")
                args.push("ihex")
                args.push(input.filePath)
                args.push(output.filePath)
                var hexcreator = "/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-objcopy"
                var cmd = new Command(hexcreator,args);
                cmd.description = 'create_hex'+project.name
                return cmd;
            }
        }
    }
}
