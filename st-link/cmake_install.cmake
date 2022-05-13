# Install script for directory: /home/evg/SOFT/Github/Arm/st-link

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so.1.7.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/evg/SOFT/Github/Arm/st-link/lib/libstlink.so.1.7.0"
    "/home/evg/SOFT/Github/Arm/st-link/lib/libstlink.so.1"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so.1.7.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/evg/SOFT/Github/Arm/st-link/lib/libstlink.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libstlink.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/evg/SOFT/Github/Arm/st-link/lib/libstlink.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-flash" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-flash")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-flash"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/evg/SOFT/Github/Arm/st-link/bin/st-flash")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-flash" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-flash")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-flash"
         OLD_RPATH "/home/evg/SOFT/Github/Arm/st-link/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-flash")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-info" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-info")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-info"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/evg/SOFT/Github/Arm/st-link/bin/st-info")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-info" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-info")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-info"
         OLD_RPATH "/home/evg/SOFT/Github/Arm/st-link/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-info")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-util" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-util")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-util"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/evg/SOFT/Github/Arm/st-link/bin/st-util")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-util" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-util")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-util"
         OLD_RPATH "/home/evg/SOFT/Github/Arm/st-link/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-util")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-trace" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-trace")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-trace"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/evg/SOFT/Github/Arm/st-link/bin/st-trace")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-trace" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-trace")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-trace"
         OLD_RPATH "/home/evg/SOFT/Github/Arm/st-link/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/st-trace")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/stlink/chips/F03x.chip;/usr/local/stlink/chips/F04x.chip;/usr/local/stlink/chips/F05x.chip;/usr/local/stlink/chips/F07x.chip;/usr/local/stlink/chips/F09x.chip;/usr/local/stlink/chips/F1xx_CL.chip;/usr/local/stlink/chips/F1xx_HD.chip;/usr/local/stlink/chips/F1xx_LD.chip;/usr/local/stlink/chips/F1xx_MD.chip;/usr/local/stlink/chips/F1xx_VL_HD.chip;/usr/local/stlink/chips/F1xx_VL_MD_LD.chip;/usr/local/stlink/chips/F1xx_XLD.chip;/usr/local/stlink/chips/F2xx.chip;/usr/local/stlink/chips/F301_F302_F318.chip;/usr/local/stlink/chips/F302_F303_F358.chip;/usr/local/stlink/chips/F302_F303_F398_HD.chip;/usr/local/stlink/chips/F303_F328_F334.chip;/usr/local/stlink/chips/F37x.chip;/usr/local/stlink/chips/F401xB_xC.chip;/usr/local/stlink/chips/F401xD_xE.chip;/usr/local/stlink/chips/F410.chip;/usr/local/stlink/chips/F411xC_xE.chip;/usr/local/stlink/chips/F412.chip;/usr/local/stlink/chips/F413_F423.chip;/usr/local/stlink/chips/F42x_F43x.chip;/usr/local/stlink/chips/F446.chip;/usr/local/stlink/chips/F46x_F47x.chip;/usr/local/stlink/chips/F4x5_F4x7.chip;/usr/local/stlink/chips/F72x_F73x.chip;/usr/local/stlink/chips/F74x_F75x.chip;/usr/local/stlink/chips/F76x_F77x.chip;/usr/local/stlink/chips/G03x_G04x.chip;/usr/local/stlink/chips/G05x_G06x.chip;/usr/local/stlink/chips/G07x_G08x.chip;/usr/local/stlink/chips/G0Bx_G0Cx.chip;/usr/local/stlink/chips/G43x_G44x.chip;/usr/local/stlink/chips/G47x_G48x.chip;/usr/local/stlink/chips/G49x_G4Ax.chip;/usr/local/stlink/chips/H72x_H73x.chip;/usr/local/stlink/chips/H74x_H75x.chip;/usr/local/stlink/chips/H7Ax_H7Bx.chip;/usr/local/stlink/chips/L0xxx_Cat_1.chip;/usr/local/stlink/chips/L0xxx_Cat_2.chip;/usr/local/stlink/chips/L0xxx_Cat_3.chip;/usr/local/stlink/chips/L0xxx_Cat_5.chip;/usr/local/stlink/chips/L1xx_Cat_1.chip;/usr/local/stlink/chips/L1xx_Cat_2.chip;/usr/local/stlink/chips/L1xx_Cat_3.chip;/usr/local/stlink/chips/L1xx_Cat_4.chip;/usr/local/stlink/chips/L1xx_Cat_5.chip;/usr/local/stlink/chips/L41x_L42x.chip;/usr/local/stlink/chips/L43x_L44x.chip;/usr/local/stlink/chips/L45x_L46x.chip;/usr/local/stlink/chips/L47x_L48x.chip;/usr/local/stlink/chips/L496x_L4A6x.chip;/usr/local/stlink/chips/L4Px.chip;/usr/local/stlink/chips/L4Rx.chip;/usr/local/stlink/chips/WBx0_WBx5.chip;/usr/local/stlink/chips/WLx5.chip;/usr/local/stlink/chips/unknown_device.chip")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/stlink/chips" TYPE FILE FILES
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F03x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F04x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F05x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F07x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F09x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F1xx_CL.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F1xx_HD.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F1xx_LD.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F1xx_MD.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F1xx_VL_HD.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F1xx_VL_MD_LD.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F1xx_XLD.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F2xx.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F301_F302_F318.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F302_F303_F358.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F302_F303_F398_HD.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F303_F328_F334.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F37x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F401xB_xC.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F401xD_xE.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F410.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F411xC_xE.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F412.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F413_F423.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F42x_F43x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F446.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F46x_F47x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F4x5_F4x7.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F72x_F73x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F74x_F75x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/F76x_F77x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/G03x_G04x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/G05x_G06x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/G07x_G08x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/G0Bx_G0Cx.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/G43x_G44x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/G47x_G48x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/G49x_G4Ax.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/H72x_H73x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/H74x_H75x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/H7Ax_H7Bx.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L0xxx_Cat_1.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L0xxx_Cat_2.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L0xxx_Cat_3.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L0xxx_Cat_5.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L1xx_Cat_1.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L1xx_Cat_2.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L1xx_Cat_3.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L1xx_Cat_4.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L1xx_Cat_5.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L41x_L42x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L43x_L44x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L45x_L46x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L47x_L48x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L496x_L4A6x.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L4Px.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/L4Rx.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/WBx0_WBx5.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/WLx5.chip"
    "/home/evg/SOFT/Github/Arm/st-link/config/chips/unknown_device.chip"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/etc/modprobe.d/stlink_v1.conf")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/etc/modprobe.d" TYPE FILE FILES "/home/evg/SOFT/Github/Arm/st-link/config/modprobe.d/stlink_v1.conf")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/lib/udev/rules.d/49-stlinkv1.rules;/lib/udev/rules.d/49-stlinkv2-1.rules;/lib/udev/rules.d/49-stlinkv2.rules;/lib/udev/rules.d/49-stlinkv3.rules")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/lib/udev/rules.d" TYPE FILE FILES
    "/home/evg/SOFT/Github/Arm/st-link/config/udev/rules.d/49-stlinkv1.rules"
    "/home/evg/SOFT/Github/Arm/st-link/config/udev/rules.d/49-stlinkv2-1.rules"
    "/home/evg/SOFT/Github/Arm/st-link/config/udev/rules.d/49-stlinkv2.rules"
    "/home/evg/SOFT/Github/Arm/st-link/config/udev/rules.d/49-stlinkv3.rules"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/evg/SOFT/Github/Arm/st-link/inc/cmake_install.cmake")
  include("/home/evg/SOFT/Github/Arm/st-link/src/stlink-gui/cmake_install.cmake")
  include("/home/evg/SOFT/Github/Arm/st-link/tests/cmake_install.cmake")
  include("/home/evg/SOFT/Github/Arm/st-link/cmake/packaging/cmake_install.cmake")
  include("/home/evg/SOFT/Github/Arm/st-link/doc/man/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/evg/SOFT/Github/Arm/st-link/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
