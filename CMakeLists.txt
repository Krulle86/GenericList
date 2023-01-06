cmake_minimum_required(VERSION 3.16)

project(ExampleGenericList VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Core Gui Qml Quick REQUIRED)

add_subdirectory ( genericListModel )

include_directories(
    genericListModel/
)

qt_add_executable(appExampleGenericList
    main.cpp
#    genericListModel/genericlistmodel.h genericListModel/genericlistmodel.cpp
#    genericListModel/genericitemlist.cpp genericListModel/genericitemlist.h
#    genericListModel/RegisterTypes.h

    specialicedlist.h specialicedlist.cpp
    specialiceditem.h specialiceditem.cpp
)

qt_add_qml_module(appExampleGenericList
    URI ExampleGenericList
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(appExampleGenericList PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appExampleGenericList PRIVATE
    Qt6::Quick
    GenericList
)

install(TARGETS appExampleGenericList
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
