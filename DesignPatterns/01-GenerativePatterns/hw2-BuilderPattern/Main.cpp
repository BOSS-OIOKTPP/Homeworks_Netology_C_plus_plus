#include <iostream>
#include <windows.h>
#include <cassert>
#include "sql_query_builder.h"



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");    
    query_builder.AddWhere({ {"id", "42"}, {"name", "John"} });  // Используем AddWhere с map

    // Тест
    std::string result = query_builder.BuildQuery();
    assert(result == "SELECT name, phone FROM students WHERE id=42 AND name=John;");

    // если нет ошибки, то выводим на экран
    std::cout << result << std::endl;

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

