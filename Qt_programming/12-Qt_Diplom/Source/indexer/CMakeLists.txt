cmake_minimum_required(VERSION 3.14)

project(indexer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive- /utf-8)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

add_executable(indexer
  ../DatabaseManager/DbManager.cpp
  ../DatabaseManager/DbManager.h
  Indexer.cpp
  Indexer.h
  main.cpp
)
target_link_libraries(indexer Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql)

add_custom_command(TARGET indexer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
            $<TARGET_FILE_DIR:indexer>/config.ini
    COMMENT "Копирование config.ini рядом с indexer.exe"
)

install(TARGETS indexer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
