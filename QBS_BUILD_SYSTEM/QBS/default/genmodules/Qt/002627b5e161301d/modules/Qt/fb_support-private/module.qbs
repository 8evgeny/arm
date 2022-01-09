import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "FbSupport"
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
    libNameForLinkerDebug: "Qt5FbSupport"
    libNameForLinkerRelease: "Qt5FbSupport"
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: ["QT_FB_SUPPORT_LIB"]
    cpp.includePaths: ["/usr/include/x86_64-linux-gnu/qt5","/usr/include/x86_64-linux-gnu/qt5/QtFbSupport","/usr/include/x86_64-linux-gnu/qt5/QtFbSupport/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtFbSupport/5.12.8/QtFbSupport"]
    cpp.libraryPaths: []
    isStaticLibrary: true
Group {
        files: [Qt["fb_support-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
