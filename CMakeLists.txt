cmake_minimum_required(VERSION 3.5)

project(papirus-folders-gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools)

set(PROJECT_SOURCES
       changelog.cpp
       credits.cpp
       filemanager.cpp
       help.cpp
       license.cpp
       main.cpp
       mainwindow.cpp
       papirus.cpp
       secdialog.cpp
       changelog.h
       credits.h
       filemanager.h
       help.h
       license.h
       mainwindow.h
       papirus.h
       secdialog.h
       changelog.ui
       credits.ui
       filemanager.ui
       help.ui
       license.ui
       mainwindow.ui
       papirus.ui
       polkit.cpp
       polkit.h
       polkit.ui
       secdialog.ui
       img.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(papirus-folders-gui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    if(Qt6LinguistTools_FOUND)
        qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()
else()
    if(ANDROID)
        add_library(papirus-folders-gui SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(papirus-folders-gui
            ${PROJECT_SOURCES}
        )
    endif()
    if(Qt5LinguistTools_FOUND)
        qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()
endif()

target_link_libraries(papirus-folders-gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(papirus-folders-gui PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(papirus-folders-gui)
endif()

# CPack configuration
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "pwnbait AKA Fredward Goodboy <fredwardtheincomparable@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A GUI for papirus-folders, edited with Gemini-CLI (version 1.0, model gemini-1.5-flash-001)")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/pwnbait-AKA-FredwardGoodboy/papirus-folders-gui-wayland")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.deb")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "papirus-folders, libqt6widgets6t64, libqt6gui6t64, libqt6core6t64, libqt6dbus6t64")
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES papirus.desktop DESTINATION share/applications)
install(FILES folder-logo.svg DESTINATION share/icons/hicolor/scalable/apps/${PROJECT_NAME}.svg)
include(CPack)
