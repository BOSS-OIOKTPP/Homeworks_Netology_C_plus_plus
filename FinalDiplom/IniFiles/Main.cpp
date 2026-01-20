#include <iostream>
#include <windows.h>
#include "IniFile.h"


int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8); // 65001

    IniFile config("config.ini");

    config.writeFloat("Physics", "Gravity", 9.81);
    config.writeFloat("Rendering", "Gamma", 2.2);
    config.writeString("Тест", "Значение", "Да");

    double g = config.readFloat("Physics", "Gravity", 10.0);
    double gamma = config.readFloat("Rendering", "Gamma", 2.2);
    std::string str = config.readString("Тест", "Значение", "Нет");

    std::cout << g << std::endl;
    std::cout << gamma << std::endl;
    std::cout << str << std::endl;

    config.updateFile();

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

