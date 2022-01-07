import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "XcbQpa"
    Depends { name: "Qt"; submodules: ["core","gui","core-private","gui-private","service_support-private","theme_support-private","fontdatabase_support-private","edid_support-private","linuxaccessibility_support-private","vulkan_support-private"]}

    architectures: ["x86_64"]
    targetPlatform: "linux"
    hasLibrary: true
    staticLibsDebug: []
    staticLibsRelease: []
    dynamicLibsDebug: []
    dynamicLibsRelease: ["/usr/lib/x86_64-linux-gnu/libQt5ServiceSupport.a","/usr/lib/x86_64-linux-gnu/libQt5ThemeSupport.a","/usr/lib/x86_64-linux-gnu/libQt5FontDatabaseSupport.a","/usr/lib/x86_64-linux-gnu/libfontconfig.so","/usr/lib/x86_64-linux-gnu/libfreetype.so","/usr/lib/x86_64-linux-gnu/libz.so","/usr/lib/x86_64-linux-gnu/libQt5LinuxAccessibilitySupport.a","/usr/lib/x86_64-linux-gnu/libQt5AccessibilitySupport.a","/usr/lib/x86_64-linux-gnu/libQt5VulkanSupport.a","/usr/lib/x86_64-linux-gnu/libGL.so","/usr/lib/x86_64-linux-gnu/libQt5Gui.so","/usr/lib/x86_64-linux-gnu/libQt5EdidSupport.a","/usr/lib/x86_64-linux-gnu/libQt5DBus.so","/usr/lib/x86_64-linux-gnu/libX11-xcb.so","/usr/lib/x86_64-linux-gnu/libxcb-xinput.so","/usr/lib/x86_64-linux-gnu/libxcb-icccm.so","/usr/lib/x86_64-linux-gnu/libxcb-image.so","/usr/lib/x86_64-linux-gnu/libxcb-shm.so","/usr/lib/x86_64-linux-gnu/libxcb-keysyms.so","/usr/lib/x86_64-linux-gnu/libxcb-randr.so","/usr/lib/x86_64-linux-gnu/libxcb-render-util.so","/usr/lib/x86_64-linux-gnu/libxcb-render.so","/usr/lib/x86_64-linux-gnu/libxcb-shape.so","/usr/lib/x86_64-linux-gnu/libxcb-sync.so","/usr/lib/x86_64-linux-gnu/libxcb-xfixes.so","/usr/lib/x86_64-linux-gnu/libxcb-xinerama.so","/usr/lib/x86_64-linux-gnu/libxcb-xkb.so","/usr/lib/x86_64-linux-gnu/libxcb.so","/usr/lib/x86_64-linux-gnu/libXrender.so","/usr/lib/x86_64-linux-gnu/libXext.so","/usr/lib/x86_64-linux-gnu/libX11.so","/usr/lib/x86_64-linux-gnu/libm.so","/usr/lib/x86_64-linux-gnu/libSM.so","/usr/lib/x86_64-linux-gnu/libICE.so","/usr/lib/x86_64-linux-gnu/libxkbcommon-x11.so","/usr/lib/x86_64-linux-gnu/libxkbcommon.so","/usr/lib/x86_64-linux-gnu/libdl.so"]
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: "Qt5XcbQpa"
    libNameForLinkerRelease: "Qt5XcbQpa"
    libFilePathDebug: undefined
    libFilePathRelease: "/usr/lib/x86_64-linux-gnu/libQt5XcbQpa.so.5.12.8"
    pluginTypes: []
    moduleConfig: ["lex","yacc","depend_includepath","testcase_targets","import_plugins","import_qpa_plugin","qt_build_extra","file_copies","qmake_use","qt","warn_on","release","link_prl","incremental","shared","release","linux","unix","posix","gcc","sse2","aesni","sse3","ssse3","sse4_1","sse4_2","avx","avx2","avx512f","avx512bw","avx512cd","avx512dq","avx512er","avx512ifma","avx512pf","avx512vbmi","avx512vl","compile_examples","enable_new_dtags","f16c","largefile","precompile_header","rdrnd","shani","nostrip","x86SimdAlways","prefix_build","force_independent","utf8_source","create_prl","link_prl","prepare_docs","qt_docs_targets","no_private_qt_headers_warning","QTDIR_build","qt_example_installs","exceptions_off","testcase_exceptions","explicitlib","warning_clean","no_module_headers","internal_module","relative_qt_rpath","qmake_cache","target_qt","c++11","strict_c++","c++14","c++1z","c99","c11","hide_symbols","bsymbolic_functions","need_fwd_pri","qt_install_module","compiler_supports_fpmath","create_libtool","have_target","dll","thread","opengl","dbusadaptors","dbusinterfaces","moc","resources"]
    cpp.defines: ["QT_XCB_QPA_LIB_LIB"]
    cpp.includePaths: []
    cpp.libraryPaths: []
    Group {
        files: [Qt["xcb_qpa_lib-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["dynamiclibrary"]
    }
}
