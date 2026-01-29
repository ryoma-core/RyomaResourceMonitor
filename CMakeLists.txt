cmake_minimum_required(VERSION 3.19)
project(RyomaResourceMonitor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Charts LinguistTools)

qt_standard_project_setup()

qt_add_executable(RyomaResourceMonitor
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    loginpage.h loginpage.cpp loginpage.ui
    listpage.h listpage.cpp listpage.ui
    monitoringpage.h monitoringpage.cpp monitoringpage.ui
    cpugraph.h cpugraph.cpp cpugraph.ui
    memorygraph.h memorygraph.cpp memorygraph.ui
    diskgraph.h diskgraph.cpp diskgraph.ui
    socketworker.h socketworker.cpp
    adddialog.h adddialog.cpp adddialog.ui
)


target_include_directories(RyomaResourceMonitor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)


qt_add_translations(
    TARGETS RyomaResourceMonitor
    TS_FILES RyomaResourceMonitor_ko_KR.ts
)

target_link_libraries(RyomaResourceMonitor
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
)

include(GNUInstallDirs)

install(TARGETS RyomaResourceMonitor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET RyomaResourceMonitor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

add_library(clientsocketlib STATIC IMPORTED GLOBAL)

set_target_properties(clientsocketlib PROPERTIES
    IMPORTED_LOCATION_DEBUG
        "${CMAKE_SOURCE_DIR}/third_party/clientsocketlib/lib/mingw/Debug/libclientsocketlib.a"
    IMPORTED_LOCATION_RELEASE
        "${CMAKE_SOURCE_DIR}/third_party/clientsocketlib/lib/mingw/Release/libclientsocketlib.a"
    INTERFACE_INCLUDE_DIRECTORIES
        "${CMAKE_SOURCE_DIR}/third_party/clientsocketlib/include"
)

target_link_libraries(RyomaResourceMonitor PRIVATE clientsocketlib ws2_32)
