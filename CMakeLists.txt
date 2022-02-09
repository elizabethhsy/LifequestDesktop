cmake_minimum_required(VERSION 3.0.0)
project(LifequestDesktop VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QT_VERSION 5)
set(REQUIRED_LIBS Sql Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt5/")
    # or list(APPEND CMAKE_PREFIX_PATH "/home/someuser/Qt/5.15.1/clang_64")
endif()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_executable(LifequestDesktop
    database.cpp
    gui.cpp
    main.cpp
    version.cpp
)

target_link_libraries(LifequestDesktop Qt5::Core Qt5::Sql Qt5::Widgets)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
