#include <iostream>
#include <windows.h>
#include "IniFile.h"
#include "SpiderClient.h"



int main() {
    // Установка кодировки консоли Windows
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8); // 65001

    // Читаем настройки
    IniFile config("config.ini");

    std::string url = config.readString("URL", "start", "http://info.cern.ch/");
    
    //double gamma = config.readFloat("Rendering", "Gamma", 2.2);
    //std::string str = config.readString("Тест", "Значение", "Нет");

    


    SpiderClient spider;
    try {
        std::string html = spider.fetch(url);
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

