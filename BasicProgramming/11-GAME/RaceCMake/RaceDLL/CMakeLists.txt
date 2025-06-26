cmake_minimum_required(VERSION 3.22)
project(my_complicated_cmake_project LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Список исходных файлов приложения
set(RACE_SOURCES
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
