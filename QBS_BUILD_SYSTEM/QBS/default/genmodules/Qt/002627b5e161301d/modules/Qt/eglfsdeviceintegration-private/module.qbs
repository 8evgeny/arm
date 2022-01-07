import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "EglFSDeviceIntegration"
    Depends { name: "Qt"; submodules: ["core","gui","core-private","gui-private","devicediscovery_support-private","eventdispatcher_support-private","service_support-private","theme_support-private","fontdatabase_support-private","fb_support-private","egl_support-private","input_support-private","platformcompositor_support-private"]}

    architectures: ["x86_64"]
    targetPlatform: "linux"
    hasLibrary: true
    staticLibsDebug: []
    staticLibsRelease: []
    dynamicLibsDebug: []
    dynamicLibsRelease: ["/usr/lib/x86_64-linux-gnu/libQt5EventDispatcherSupport.a","/usr/lib/x86_64-linux-gnu/libgthread-2.0.so","/usr/lib/x86_64-linux-gnu/libglib-2.0.so","/usr/lib/x86_64-linux-gnu/libQt5ServiceSupport.a","/usr/lib/x86_64-linux-gnu/libQt5ThemeSupport.a","/usr/lib/x86_64-linux-gnu/libQt5FontDatabaseSupport.a","/usr/lib/x86_64-linux-gnu/libfontconfig.so","/usr/lib/x86_64-linux-gnu/libfreetype.so","/usr/lib/x86_64-linux-gnu/libz.so","/usr/lib/x86_64-linux-gnu/libQt5FbSupport.a","/usr/lib/x86_64-linux-gnu/libQt5EglSupport.a","/usr/lib/x86_64-linux-gnu/libEGL.so","/usr/lib/x86_64-linux-gnu/libXext.so","/usr/lib/x86_64-linux-gnu/libX11.so","/usr/lib/x86_64-linux-gnu/libm.so","/usr/lib/x86_64-linux-gnu/libQt5InputSupport.a","/usr/lib/x86_64-linux-gnu/libmtdev.so","/usr/lib/x86_64-linux-gnu/libinput.so","/usr/lib/x86_64-linux-gnu/libxkbcommon.so","/usr/lib/x86_64-linux-gnu/libQt5PlatformCompositorSupport.a","/usr/lib/x86_64-linux-gnu/libGL.so","/usr/lib/x86_64-linux-gnu/libQt5Gui.so","/usr/lib/x86_64-linux-gnu/libQt5DeviceDiscoverySupport.a","/lib/x86_64-linux-gnu/libudev.so","/usr/lib/x86_64-linux-gnu/libQt5DBus.so","/usr/lib/x86_64-linux-gnu/libdl.so"]
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: "Qt5EglFSDeviceIntegration"
    libNameForLinkerRelease: "Qt5EglFSDeviceIntegration"
    libFilePathDebug: undefined
    libFilePathRelease: "/usr/lib/x86_64-linux-gnu/libQt5EglFSDeviceIntegration.so.5.12.8"
    pluginTypes: []
    moduleConfig: ["lex","yacc","depend_includepath","testcase_targets","import_plugins","import_qpa_plugin","qt_build_extra","file_copies","qmake_use","qt","warn_on","release","link_prl","incremental","shared","release","linux","unix","posix","gcc","sse2","aesni","sse3","ssse3","sse4_1","sse4_2","avx","avx2","avx512f","avx512bw","avx512cd","avx512dq","avx512er","avx512ifma","avx512pf","avx512vbmi","avx512vl","compile_examples","enable_new_dtags","f16c","largefile","precompile_header","rdrnd","shani","nostrip","x86SimdAlways","prefix_build","force_independent","utf8_source","create_prl","link_prl","prepare_docs","qt_docs_targets","no_private_qt_headers_warning","QTDIR_build","qt_example_installs","exceptions_off","testcase_exceptions","explicitlib","warning_clean","internal_module","egl","relative_qt_rpath","qmake_cache","target_qt","c++11","strict_c++","c++14","c++1z","c99","c11","hide_symbols","bsymbolic_functions","qt_install_headers","need_fwd_pri","qt_install_module","compiler_supports_fpmath","create_libtool","have_target","dll","thread","opengl","dbusadaptors","dbusinterfaces","moc","resources"]
    cpp.defines: ["QT_EGLFSDEVICEINTEGRATION_LIB"]
    cpp.includePaths: ["/usr/include/x86_64-linux-gnu/qt5","/usr/include/x86_64-linux-gnu/qt5/QtEglFSDeviceIntegration","/usr/include/x86_64-linux-gnu/qt5/QtEglFSDeviceIntegration/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtEglFSDeviceIntegration/5.12.8/QtEglFSDeviceIntegration"]
    cpp.libraryPaths: []
    Group {
        files: [Qt["eglfsdeviceintegration-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["dynamiclibrary"]
    }
}
