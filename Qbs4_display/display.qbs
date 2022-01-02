import qbs
Project {
    name: "display"
    Product {
        name: "milandr_display"
        type: [
            "elf",
            "hex",
            "bin",
        ]
        Group {
            name: "src_c"
            prefix: "src/"
            files: [
                "gpio.c",
                "logic.c",
                "mt20s4.c",
                "rcc_delay.c",
                "usb.c",
                "var.c",
            ]
            fileTags: ['c']
        }
        Group {
            name: "src_cpp"
            prefix: "src/"
            files: [
                "main.cpp"
            ]
            fileTags: ['cpp']
        }

        Rule {
            inputs: ["c"]
            Artifact {
                fileTags: ['obj']
                filePath: input.fileName + '.o'
            }
            prepare: {
                var args = [];
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
                var compilerPath = "/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-gcc"
                var cmd = new Command(compilerPath, args);
                cmd.description = 'compiling ' + input.fileName;
                cmd.highlight = 'compiler';
                cmd.silent = false;
                return cmd;
            }
        }

        Rule {
            inputs: ["cpp"]
            Artifact {
                fileTags: ['obj']
                filePath: input.fileName + '.o'
            }
            prepare: {
                var args = [];
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
                var compilerPath = "/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-gcc"
                var cmd = new Command(compilerPath, args);
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
                args.push("-T/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-ld")
                args.push('-o');
                args.push(output.filePath);
                var compilerPath = "/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-gcc"
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
