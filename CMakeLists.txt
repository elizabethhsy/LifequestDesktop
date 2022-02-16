cmake_minimum_required(VERSION 3.0.0)
project(LifequestDesktop VERSION 0.1.0)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Sql Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt5/")
    # or list(APPEND CMAKE_PREFIX_PATH "/home/someuser/Qt/5.15.1/clang_64")
endif()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/*.qss"
)

add_executable(LifequestDesktop ${all_SRCS})

target_link_libraries(LifequestDesktop Qt5::Core Qt5::Sql Qt5::Widgets)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
