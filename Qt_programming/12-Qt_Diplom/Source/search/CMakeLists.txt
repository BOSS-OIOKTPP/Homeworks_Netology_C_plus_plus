cmake_minimum_required(VERSION 3.14)

project(search LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive- /utf-8)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

add_executable(search WIN32
  ../DatabaseManager/DbManager.cpp
  ../DatabaseManager/DbManager.h
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
)
target_link_libraries(search Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

add_custom_command(TARGET search POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
            $<TARGET_FILE_DIR:search>/config.ini
    COMMENT "Копирование config.ini рядом с search.exe"
)
