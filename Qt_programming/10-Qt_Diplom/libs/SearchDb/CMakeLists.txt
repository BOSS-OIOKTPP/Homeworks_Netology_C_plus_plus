# Логика БД для диплома (QtSql + PostgreSQL); настройки — через QSettings (INI)
add_library(searchdb STATIC
    SearchDatabase.cpp
    TextIndex.cpp
)

target_link_libraries(searchdb PUBLIC
    Qt6::Core
    Qt6::Sql
)

target_include_directories(searchdb PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(searchdb PROPERTIES AUTOMOC OFF)
