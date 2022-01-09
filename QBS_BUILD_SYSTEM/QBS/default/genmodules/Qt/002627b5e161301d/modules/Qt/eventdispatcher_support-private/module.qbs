import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "EventDispatcherSupport"
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
    libNameForLinkerDebug: "Qt5EventDispatcherSupport"
    libNameForLinkerRelease: "Qt5EventDispatcherSupport"
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: ["QT_EVENTDISPATCHER_SUPPORT_LIB"]
    cpp.includePaths: ["/usr/include/x86_64-linux-gnu/qt5","/usr/include/x86_64-linux-gnu/qt5/QtEventDispatcherSupport","/usr/include/x86_64-linux-gnu/qt5/QtEventDispatcherSupport/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtEventDispatcherSupport/5.12.8/QtEventDispatcherSupport"]
    cpp.libraryPaths: []
    isStaticLibrary: true
Group {
        files: [Qt["eventdispatcher_support-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
