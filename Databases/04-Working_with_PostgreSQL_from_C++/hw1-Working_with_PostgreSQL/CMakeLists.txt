cmake_minimum_required(VERSION 3.22)
project(hw1-Working_with_PostgreSQL)

# Правильный путь к PostgreSQL
set(PostgreSQL_ROOT "C:/Program Files/PostgreSQL/18")  
set(PKG_CONFIG_EXECUTABLE FALSE)

# Путь к libpqxx++
add_subdirectory(libpqxx-master)

add_executable(${PROJECT_NAME} 
    src/Main.cpp 
 "src/ClientUtil.cpp" "src/ClientUtil.h")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE pqxx)