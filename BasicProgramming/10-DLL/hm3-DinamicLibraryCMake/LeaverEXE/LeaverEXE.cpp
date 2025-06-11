#include <iostream>
#include <windows.h>
#include <string>
#include "Leaver.h"

int main()
{
    // Устанавливаем кодировку консоли
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::string Word;
    Leaver L;

    std::cout << "Введите имя: ";
    std::getline(std::cin >> std::ws, Word);

    std::cout << L.leave(Word) << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}