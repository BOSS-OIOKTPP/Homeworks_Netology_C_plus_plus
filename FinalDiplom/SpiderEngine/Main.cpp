#include <iostream>
#include <windows.h>
#include "IniFile.h"
#include "SpiderEngine.h"



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8); // 65001

    // 1. Читаем конфигурацию
    IniFile config("config.ini");

    // 2. Настройки БД
    std::string host = config.readString("Database", "Host", "localhost");
    std::string port = config.readString("Database", "Port", "5432");
    std::string name = config.readString("Database", "Name", "spider_db");
    std::string user = config.readString("Database", "User", "spider_user");
    std::string pass = config.readString("Database", "Password", "secure_password");
    // Строка соединения с БД
    std::string connection_string =
        "host=" + host + " " +
        "port=" + port + " " +
        "dbname=" + name + " " +
        "user=" + user + " " +
        "password=" + pass;
    // 3. Стартовая ссылка и глубина 
    std::string startUrl = config.readString("Spider", "StartUrl", "http://info.cern.ch/");
    int maxDepth = std::stoi(config.readString("Spider", "MaxDepth", "1"));

    try {
        // 4. Подключаемся к БД
        DatabaseManager db(connection_string);
        db.Connect();
        db.CreateTables();

        // 5. Запускаем обход
        SpiderEngine engine(startUrl, maxDepth, db);
        engine.Run();
    }
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << "\n";
        return 1;
    }

    

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
