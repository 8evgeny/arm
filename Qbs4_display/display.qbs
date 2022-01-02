import qbs
Project {
    name: "simple"
    Product {
        name: "micro"
        type: "hex"
        Group {
            name: "sources"
            files: ["main.c",
                    "system_MDR32F9Qx.c",
                    "startup_Cortex_M3.c"]
            fileTags: ['c']
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
