cmake_minimum_required(VERSION 3.5)

project(VirtualFPGA LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

add_executable(VirtualFPGA
    src/main.cpp
    src/mainwindow.cpp
    src/model.cpp
    src/fileselectdialog.cpp
    src/settingsdialog.cpp
    src/graderdialog.cpp

    include/fileselectdialog.h
    include/indexedswitch.h
    include/indexedbutton.h
    include/model.h
    include/mainwindow.h
    include/settingsdialog.h
    include/versionmessage.h
    include/version.h
    include/graderdialog.h

    forms/fileselectdialog.ui
    forms/mainwindow.ui
    forms/settingsdialog.ui
    forms/graderdialog.ui

    resources/resources.qrc
)

target_include_directories(VirtualFPGA PUBLIC
    include
    forms
)

target_link_libraries(VirtualFPGA PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
