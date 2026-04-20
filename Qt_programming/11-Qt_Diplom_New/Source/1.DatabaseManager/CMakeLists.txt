cmake_minimum_required(VERSION 3.16)

project(DatabaseManagerQtConsole LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Sql)

qt_standard_project_setup()

qt_add_executable(DatabaseManagerQtConsole
    main.cpp
    DatabaseManager.cpp
    DatabaseManager.h
)

target_link_libraries(DatabaseManagerQtConsole PRIVATE
    Qt6::Core
    Qt6::Sql
)
