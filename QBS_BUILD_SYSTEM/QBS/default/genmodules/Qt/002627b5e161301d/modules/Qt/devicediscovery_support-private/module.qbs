import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "DeviceDiscoverySupport"
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
    libNameForLinkerDebug: "Qt5DeviceDiscoverySupport"
    libNameForLinkerRelease: "Qt5DeviceDiscoverySupport"
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: ["QT_DEVICEDISCOVERY_SUPPORT_LIB"]
    cpp.includePaths: ["/usr/include/x86_64-linux-gnu/qt5","/usr/include/x86_64-linux-gnu/qt5/QtDeviceDiscoverySupport","/usr/include/x86_64-linux-gnu/qt5/QtDeviceDiscoverySupport/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtDeviceDiscoverySupport/5.12.8/QtDeviceDiscoverySupport"]
    cpp.libraryPaths: []
    isStaticLibrary: true
Group {
        files: [Qt["devicediscovery_support-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
