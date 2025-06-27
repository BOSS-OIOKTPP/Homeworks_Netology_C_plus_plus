cmake_minimum_required(VERSION 3.22)
project(RaceCMake LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам из проекта для VisualStudio
set(SOURCE_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../RaceVS")

# Выходная папка bin внутри RaceCMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)		#  .exe, .dll

# Подключаем подпроекты
add_subdirectory(RaceDLL)
add_subdirectory(RaceEXE)
