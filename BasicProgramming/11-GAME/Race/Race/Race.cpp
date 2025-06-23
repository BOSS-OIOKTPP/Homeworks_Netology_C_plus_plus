#include <iostream>
//#include <locale>
#include <string>
#include <windows.h>
#include "RaceParams.h"


int main()
{
    
    // Установка кодировки консоли Windows
    SetConsoleCP(65001);   // 1251
    SetConsoleOutputCP(65001);

    // Создали класс параметров игры
    Game game;
    int intRace;

    while (true) {
        std::cout << "Добро пожаловать в гоночный симулятор!\n";
        std::cout << "1. Гонка для наземного транспорта\n";
        std::cout << "2. Гонка для воздушного транспорта\n";
        std::cout << "3. Гонка для наземного и воздушного транспорта\n";
        std::cout << "Выберите тип гонки: ";
        
        std::cin >> intRace;
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

    }



    return EXIT_SUCCESS;
}

