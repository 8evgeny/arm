import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "KmsSupport"
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
    libNameForLinkerDebug: "Qt5KmsSupport"
    libNameForLinkerRelease: "Qt5KmsSupport"
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: ["QT_KMS_SUPPORT_LIB"]
    cpp.includePaths: ["/usr/include/x86_64-linux-gnu/qt5","/usr/include/x86_64-linux-gnu/qt5/QtKmsSupport","/usr/include/x86_64-linux-gnu/qt5/QtKmsSupport/5.12.8","/usr/include/x86_64-linux-gnu/qt5/QtKmsSupport/5.12.8/QtKmsSupport"]
    cpp.libraryPaths: []
    isStaticLibrary: true
Group {
        files: [Qt["kms_support-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
