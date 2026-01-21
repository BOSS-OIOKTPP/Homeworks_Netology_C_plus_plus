#include <iostream>
#include <windows.h>
#include <pqxx/pqxx>
#include "IniFile.h"
#include "DatabaseManager.h"



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8); // 65001

    // Читаем настройки
    IniFile config("config.ini");
    // БД
    std::string host = config.readString("Database", "Host", "localhost");
    std::string port = config.readString("Database", "Port", "5432");
    std::string name = config.readString("Database", "Name", "spider_db");
    std::string user = config.readString("Database", "User", "spider_user");
    std::string pass = config.readString("Database", "Password", "");
    // Стартовая ссылка и глубина 
    std::string startUrl = config.readString("Spider", "StartUrl", "http://example.com");
    int maxDepth = std::stoi(config.readString("Spider", "MaxDepth", "1"));
    
    // Строка соединения с БД
    std::string connection_string =
        "host="     + host + " " +
        "port="     + port + " " +
        "dbname="   + name + " " +
        "user="     + user + " " +
        "password=" + pass;


    std::cout << "Проверка библиотеки libpqxx:" << std::endl;
    try {
        std::cout << "Version: " << PQXX_VERSION << std::endl;
        std::cout << "Готова к работе!" << std::endl << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
    std::cout << std::endl;

   
    // Создаем объект для работы с базой данных
    DatabaseManager bd(connection_string);
    // Соединяемся с базой данных
    try {
        bd.Connect();
    }
    catch (const std::exception& e) {
        std::cout << "ОШИБКА. Не удалось подключится к базе данных: " << e.what() << std::endl;
        return 1;
    }

    // Информация о базе данных
    std::cout << "Соединение с базой данных установлено:" << std::endl;
    std::cout << bd.GetDatabaseInfo() << std::endl;
    std::cout << std::endl;

    // 1. Создаем таблицы - если не получилось, выходим
    try {
        bd.CreateTables();
        std::cerr << "Таблицы успешно созданы. " << std::endl;
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ОШИБКА. Не удалось создать таблицы. " << e.what() << std::endl;
        std::cout << std::endl;
        return 1;
    }

   
    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

