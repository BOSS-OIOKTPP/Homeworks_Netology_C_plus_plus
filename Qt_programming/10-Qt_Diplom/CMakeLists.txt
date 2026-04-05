# Диплом Qt: библиотека SearchDb (БД), демо db_demo, приложения indexer и searcher; INI — QSettings
# Открывайте эту папку в Qt Creator: Файл → Открыть файл или проект → CMakeLists.txt
# Kit: Qt 6.4.x, CMake, компилятор MinGW или MSVC (укажите CMAKE_PREFIX_PATH на Qt, например C:/Qt/6.4.2/mingw_64)

cmake_minimum_required(VERSION 3.16)
project(QtSearchSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Sql Widgets)

add_subdirectory(libs/SearchDb)

add_subdirectory(apps/db_demo)
add_subdirectory(apps/indexer)
add_subdirectory(apps/searcher)
