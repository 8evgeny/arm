import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "InputSupport"
    Depends { name: "Qt"; submodules: ["core-private","gui-private","devicediscovery_support-private"]}

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
    libNameForLinkerDebug: "Qt5InputSupport"
    libNameForLinkerRelease: "Qt5InputSupport"
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: ["QT_INPUT_SUPPORT_LIB"]
    cpp.includePaths: ["/usr/include/x86_64-linux-gnu/qt5","/usr/include/x86_64-linux-gnu/qt5/QtInputSupport","/usr/include/x86_64-linux-gnu/qt5/QtInputSupport/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtInputSupport/5.12.8/QtInputSupport"]
    cpp.libraryPaths: []
    isStaticLibrary: true
Group {
        files: [Qt["input_support-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
