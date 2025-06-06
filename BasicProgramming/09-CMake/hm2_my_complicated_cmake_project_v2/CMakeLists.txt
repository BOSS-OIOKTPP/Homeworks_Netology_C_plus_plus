cmake_minimum_required(VERSION 3.22)
project(my_complicated_cmake_project LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Список исходных файлов
set(SOURCES
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

# Список заголовочных файлов
set(HEADERS
    include/Polygon.h
    include/Quadrilateral.h
    include/QuadrilateralParallelogram.h
    include/QuadrilateralRect.h
    include/QuadrilateralRhomb.h
    include/QuadrilateralSquare.h
    include/Triangle.h
    include/TriangleEquilateral.h
    include/TriangleIsosceles.h
    include/TriangleRight.h
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Указываем путь к заголовочным файлам (для компилятора)
target_include_directories(${PROJECT_NAME} PRIVATE include)