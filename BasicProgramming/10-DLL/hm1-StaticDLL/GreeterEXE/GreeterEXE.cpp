#include <iostream>
#include <windows.h>
#include <string>
#include "GreeterDLL.h"

int main()
{
    // Устанавливаем кодировку консоли
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::string Word;
    Greeter G;

    std::cout << "Введите имя: ";
    std::getline(std::cin >> std::ws, Word);

    std::cout << G.greet(Word) << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

