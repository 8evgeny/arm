import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "Bootstrap"
    Depends { name: "Qt"; submodules: []}

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
    libNameForLinkerDebug: "Qt5Bootstrap"
    libNameForLinkerRelease: "Qt5Bootstrap"
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: ["QT_BOOTSTRAP_LIB","QT_VERSION_STR=\\'\\\"5.12.8\\\"\\'","QT_VERSION_MAJOR=5","QT_VERSION_MINOR=12","QT_VERSION_PATCH=8","QT_BOOTSTRAPPED","QT_NO_CAST_TO_ASCII"]
    cpp.includePaths: ["/usr/include/x86_64-linux-gnu/qt5","/usr/include/x86_64-linux-gnu/qt5/QtCore","/usr/include/x86_64-linux-gnu/qt5/QtCore/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtCore/5.12.8/QtCore","/usr/include/x86_64-linux-gnu/qt5/QtXml","/usr/include/x86_64-linux-gnu/qt5/QtXml/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtXml/5.12.8/QtXml"]
    cpp.libraryPaths: []
    isStaticLibrary: true
Group {
        files: [Qt["bootstrap-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
