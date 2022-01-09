import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "PlatformCompositorSupport"
    Depends { name: "Qt"; submodules: ["core-private","gui-private"]}

    architectures: ["x86_64"]
    targetPlatform: "linux"
    hasLibrary: true
    staticLibsDebug: []
    staticLibsRelease: []
    dynamicLibsDebug: []
    dynamicLibsRelease: []
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: "Qt5PlatformCompositorSupport"
    libNameForLinkerRelease: "Qt5PlatformCompositorSupport"
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: ["QT_PLATFORMCOMPOSITOR_SUPPORT_LIB"]
    cpp.includePaths: ["/usr/include/x86_64-linux-gnu/qt5","/usr/include/x86_64-linux-gnu/qt5/QtPlatformCompositorSupport","/usr/include/x86_64-linux-gnu/qt5/QtPlatformCompositorSupport/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtPlatformCompositorSupport/5.12.8/QtPlatformCompositorSupport"]
    cpp.libraryPaths: []
    isStaticLibrary: true
Group {
        files: [Qt["platformcompositor_support-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
