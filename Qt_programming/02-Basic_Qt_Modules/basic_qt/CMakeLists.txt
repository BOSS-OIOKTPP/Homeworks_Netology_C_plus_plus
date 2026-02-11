cmake_minimum_required(VERSION 3.14)

project(basic_qt LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Network
    Sql)
find_package(Qt6 REQUIRED COMPONENTS )


add_executable(basic_qt
  main.cpp
)
target_link_libraries(basic_qt PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Sql)

