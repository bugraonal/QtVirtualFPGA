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
    src/modelthread.cpp
#    src/indexedbutton.cpp
#    src/indexedswitch.cpp

    include/indexedswitch.h
    include/indexedbutton.h
    include/mainwindow.h
    include/modelthread.h
    forms/mainwindow.ui
    resources/resources.qrc
)

target_include_directories(VirtualFPGA PUBLIC
    include
    forms
)

target_link_libraries(VirtualFPGA PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
