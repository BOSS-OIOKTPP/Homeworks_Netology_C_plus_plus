cmake_minimum_required(VERSION 3.22)
project(Race LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Пути к файлам
set(SOURCE_DIR ../../Race/RaceObject)
set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

# Список исходных файлов
file(GLOB SOURCES
    ${SOURCE_DIR}/*.cpp
    ../../Race/Race/Race.cpp
)

# Список заголовочных файлов (для IDE)
file(GLOB HEADERS
    ${SOURCE_DIR}/*.h
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS}  # Заголовки добавляются только для IDE
)

# Указываем пути к заголовкам
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SOURCE_DIR}
    ../../Race/Race/
)

# Установка выходной директории
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

# Удаляем все определения, связанные с DLL (если они есть)
target_compile_definitions(${PROJECT_NAME} PRIVATE)