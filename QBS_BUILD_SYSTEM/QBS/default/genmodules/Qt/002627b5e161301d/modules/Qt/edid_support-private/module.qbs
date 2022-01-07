import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "EdidSupport"
    Depends { name: "Qt"; submodules: ["core-private"]}

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
    libNameForLinkerDebug: "Qt5EdidSupport"
    libNameForLinkerRelease: "Qt5EdidSupport"
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: ["QT_EDID_SUPPORT_LIB"]
    cpp.includePaths: ["/usr/include/x86_64-linux-gnu/qt5","/usr/include/x86_64-linux-gnu/qt5/QtEdidSupport","/usr/include/x86_64-linux-gnu/qt5/QtEdidSupport/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtEdidSupport/5.12.8/QtEdidSupport"]
    cpp.libraryPaths: []
    isStaticLibrary: true
Group {
        files: [Qt["edid_support-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
