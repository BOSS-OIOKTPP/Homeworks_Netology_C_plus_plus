cmake_minimum_required(VERSION 3.22)
project(Race LANGUAGES CXX)

# Исходник из RaceVS/RaceEXE/
set(SOURCES
    ${SOURCE_BASE_DIR}/Race/Race.cpp
)

# Создаем EXE
add_executable(${PROJECT_NAME} ${SOURCES})

# Линкуем DLL
target_link_libraries(${PROJECT_NAME} PRIVATE RaceObject)

# Указываем путь к заголовочным файлам (для компилятора)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SOURCE_BASE_DIR}/RaceObject
)