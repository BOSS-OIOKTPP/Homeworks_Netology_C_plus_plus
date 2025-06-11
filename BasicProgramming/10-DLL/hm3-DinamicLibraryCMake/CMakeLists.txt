cmake_minimum_required(VERSION 3.22)
project(LeaverProject LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##  1
# Список исходных файлов
set(DLL_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/LeaverDLL/Leaver.cpp
) 
set(EXE_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/LeaverEXE/LeaverEXE.cpp
)
set(HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/LeaverDLL/Leaver.h
) 


##  2
# Создаем DLL
add_library(LeaverDLL SHARED ${DLL_SOURCES} ${HEADERS})

# Указываем путь к заголовочным файлам (для компилятора)
#target_include_directories(LeaverDLL PRIVATE 
#	${CMAKE_CURRENT_SOURCE_DIR}/LeaverDLL)

# Добавляем определение для экспорта
target_compile_definitions(LeaverDLL PRIVATE "LEAVERDLL_EXPORTS")


##  3
# Создаем исполняемый файл
add_executable(LeaverEXE ${EXE_SOURCES})

# Указываем путь к заголовочным файлам (для компилятора)
target_include_directories(LeaverEXE PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/LeaverDLL)

# Связываем EXE с DLL
target_link_libraries(LeaverEXE PRIVATE LeaverDLL)

# Добавляем определения для импорта
target_compile_definitions(LeaverEXE PRIVATE "LEAVERDLL_IMPORTS")