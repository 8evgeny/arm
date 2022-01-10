# Windows usage instruction
# 
# 1. Install last version of cmake from https://cmake.org/download/ into the C:/CMake.
# 2. Run command shell.
# 3. Change directoty to the gdmx-display project directory from the command prompt.
# 4. Create the directory "build" by typing "mkdir build".
# 5. Change the directory "build" by typing "cd build".
# 6. Run CMake-GUI.exe. Select the source code directory and build directory.
# 7. Choose "File->Delete Cash" from the main menu bar.
# 8. Select the Generator type: "Unix Makefiles".
# 9. Select "Specify toolchain file for cross-compiling".
# 10. Press "Next" button.
# 11. Brouse to the arm-none-eabi.cmake file.
# 12. Press "Finish" button.
# 13. Press the button "Configure".
# 14. Check for it is done sucsessfull.
# 15. Press the button "Generate".
# 16. Check for it is done sucsessfull.
# 17. Go to the command shell and type "gmake" or "c:/CMake/bin/cmake --build ."
# 18. Check for sucsessfull build.

# Toolchain configurations

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Defines for Linux
# set(TOOLCHAIN_BIN_DIR "/usr/bin")
# set(TARGET_TRIPLET "arm-none-eabi-")
# set(TOOL_EXECUTABLE_SUFFIX "")

# Defines for Windows
set(TOOLCHAIN_BIN_DIR "c:/GNU Arm Embedded Toolchain/10 2020-q4-major/bin")
set(TARGET_TRIPLET "arm-none-eabi-")
set(TOOL_EXECUTABLE_SUFFIX ".exe")

set(CMAKE_C_COMPILER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}gcc${TOOL_EXECUTABLE_SUFFIX}")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}g++${TOOL_EXECUTABLE_SUFFIX}")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}gcc${TOOL_EXECUTABLE_SUFFIX}")
set(CMAKE_OBJCOPY "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}objcopy${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "objcopy tool")
set(CMAKE_OBJDUMP "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}objdump${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "objdump tool")
set(CMAKE_SIZE "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}size${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "size tool")
set(CMAKE_DEBUGER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}gdb${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "debuger")
set(CMAKE_CPPFILT "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}c++filt${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "C++filt")
