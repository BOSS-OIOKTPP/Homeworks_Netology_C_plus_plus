cmake_minimum_required(VERSION 3.22.0)
project(my_first_cmake_project)
# Папка для выходных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../../exe)
# Собираем исполняемый файл
add_executable(my_first_cmake_program source.cpp)