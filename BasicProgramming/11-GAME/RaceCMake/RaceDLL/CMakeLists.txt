cmake_minimum_required(VERSION 3.22)
project(RaceObject  LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходники из RaceVS/RaceObject/
set(SOURCES
    ${SOURCE_BASE_DIR}/RaceObject/Boots.cpp
    ${SOURCE_BASE_DIR}/RaceObject/Broom.cpp
    ${SOURCE_BASE_DIR}/RaceObject/Camel.cpp
    ${SOURCE_BASE_DIR}/RaceObject/Centaur.cpp
    ${SOURCE_BASE_DIR}/RaceObject/Eagle.cpp
    ${SOURCE_BASE_DIR}/RaceObject/FlyingCarpet.cpp
    ${SOURCE_BASE_DIR}/RaceObject/SpeedCamel.cpp
    ${SOURCE_BASE_DIR}/RaceObject/Transport.cpp
    ${SOURCE_BASE_DIR}/RaceObject/RaceParams.cpp
)
set(HEADERS
    ${SOURCE_BASE_DIR}/RaceObject/Boots.h
    ${SOURCE_BASE_DIR}/RaceObject/Broom.h
    ${SOURCE_BASE_DIR}/RaceObject/Camel.h
    ${SOURCE_BASE_DIR}/RaceObject/Centaur.h
    ${SOURCE_BASE_DIR}/RaceObject/Eagle.h
    ${SOURCE_BASE_DIR}/RaceObject/FlyingCarpet.h
    ${SOURCE_BASE_DIR}/RaceObject/SpeedCamel.h
    ${SOURCE_BASE_DIR}/RaceObject/Transport.h
    ${SOURCE_BASE_DIR}/RaceObject/RaceParams.h
)

# Создаем DLL
add_library(${PROJECT_NAME} SHARED 
    ${SOURCES}
    ${HEADERS}
)

# Добавляем определение для экспорта
target_compile_definitions(${PROJECT_NAME} PRIVATE RACEOBJECT_EXPORTS)

# Указываем путь к заголовочным файлам (для компилятора)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${SOURCE_BASE_DIR}/RaceObject
)