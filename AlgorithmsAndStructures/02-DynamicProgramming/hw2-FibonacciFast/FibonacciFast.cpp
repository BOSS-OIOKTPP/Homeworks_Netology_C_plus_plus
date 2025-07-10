#include <iostream>
#include <string>
#include <windows.h>


void PrintFibonacci(int n) {
    // Создаем массив для хранения чисел Фибоначчи
    int* arrFib = new int[n];

    // Первое базовое число
    arrFib[0] = 0;              
    // Второе базовое число
    if (n > 1) arrFib[1] = 1;
    // Вычисляем остальные числа
    for (int i = 2; i < n; i++) { 
        arrFib[i] = arrFib[i - 1] + arrFib[i - 2]; 
    }

    // Выводим результат
    std::cout << "Последовательность Фибоначчи: ";
    for (int i = 0; i < n; i++) {        
        std::cout << arrFib[i];
        if (i != n - 1)
            std::cout << ", ";  // Запятая после всех чисел, кроме последнего
    }
    
    // Удаляем массив
    delete[] arrFib;
};


// *** Итоговое меню   ***
int MenuFinal() {
    int intReplay;
    

    while (true) {
        // Выводим меню
        std::cout << "1. Провести еще один расчет" << std::endl;
        std::cout << "2. Выйти" << std::endl;
        std::cout << "Выберите действие: ";

        std::cin >> intReplay;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (intReplay >= 1 && intReplay <= 2) {
            break;
        }

        // Очищаем консоль 
        system("cls");
    }
    return intReplay;
}


// ГЛАВНАЯ ПРОГРАММА
int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int intN{ 0 };
    int intReplay{ 0 };

    while (true) {
    
        while (true) {
            // Очищаем консоль 
            system("cls");

            std::cout << "Программа рассчитывает числа Фибоначчи по формуле F(n) = F(n-1) + F(n-2) для n > 1" << std::endl;
            std::cout << "Введите количество чисел Фибоначчи в интервале n [1; 10] : ";
            std::cin >> intN;
            std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

            if (intN > 0 && intN < 11) break;
        }

        // Выводим числа Фибоначчи
        PrintFibonacci(intN);

        // Выводим меню
        std::cout << std::endl;
        std::cout << std::endl;

        intReplay = MenuFinal();
        if (intReplay == 2) break;  // Выходим        
    }

    std::cout << std::endl;
    std::cout << "Нажмите любую клавишу для завершения программы." << std::endl;
    std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

