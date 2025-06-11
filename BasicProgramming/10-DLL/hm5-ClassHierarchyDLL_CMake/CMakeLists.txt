cmake_minimum_required(VERSION 3.22)
project(PolygonProject LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##  1
# Список исходных файлов
set(DLL_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/Polygon.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/Quadrilateral.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/QuadrilateralParallelogram.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/QuadrilateralRect.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/QuadrilateralRhomb.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/QuadrilateralSquare.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/Triangle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/TriangleEquilateral.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/TriangleIsosceles.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/TriangleRight.cpp

) 
set(EXE_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonEXE/PolygonEXE.cpp
)
set(HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/Polygon.h
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/Quadrilateral.h
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/QuadrilateralParallelogram.h
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/QuadrilateralRect.h
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/QuadrilateralRhomb.h
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/QuadrilateralSquare.h
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/Triangle.h
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/TriangleEquilateral.h
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/TriangleIsosceles.h
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL/TriangleRight.h
) 


##  2
# Создаем DLL
add_library(PolygonDLL SHARED ${DLL_SOURCES} ${HEADERS})

# Указываем путь к заголовочным файлам (для компилятора)
#target_include_directories(PolygonDLL PRIVATE 
#	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL)

# Добавляем определение для экспорта
target_compile_definitions(PolygonDLL PRIVATE "POLYGONDLL_EXPORTS")


##  3
# Создаем исполняемый файл
add_executable(PolygonEXE ${EXE_SOURCES})

# Указываем путь к заголовочным файлам (для компилятора)
target_include_directories(PolygonEXE PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/PolygonDLL)

# Связываем EXE с DLL
target_link_libraries(PolygonEXE PRIVATE PolygonDLL)

# Добавляем определения для импорта
target_compile_definitions(PolygonEXE PRIVATE "POLYGONDLL_IMPORTS")