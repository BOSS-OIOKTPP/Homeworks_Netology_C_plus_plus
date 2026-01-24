#include <iostream>
#include <windows.h>
#include "IniFile.h"
#include "SpiderClient.h"



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8); // 65001

    // Читаем настройки
    IniFile config("config.ini");
    
    // Стартовая ссылка и глубина 
    std::string startUrl = config.readString("Spider", "StartUrl", "http://example.com");
    int maxDepth = std::stoi(config.readString("Spider", "MaxDepth", "1"));
        
    
    SpiderClient spider;
    try {
        std::string html = spider.fetch(startUrl);
        std::cout << "Загружено " << html.size() << " байт.\n";

        // Сохранить в файл или передать в парсер
        std::cout << html << "\n";
    }
    
     catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;    
    }

    

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

