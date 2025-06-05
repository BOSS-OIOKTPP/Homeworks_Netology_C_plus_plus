cmake_minimum_required(VERSION 3.22.0)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(my_complicated_cmake_project)

# Подключаем заголовочные файлы
include_directories(include)

# Папка для выходных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../../exe)

# Добавляем исполняемый файл
add_executable(my_complicated_cmake_project
    src/hw3-ClassHierarchy.cpp
    src/Polygon.cpp
    src/Quadrilateral.cpp
    src/QuadrilateralParallelogram.cpp
    src/QuadrilateralRect.cpp
    src/QuadrilateralRhomb.cpp
    src/QuadrilateralSquare.cpp
    src/Triangle.cpp
    src/TriangleEquilateral.cpp
    src/TriangleIsosceles.cpp
    src/TriangleRight.cpp
)

