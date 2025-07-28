#include <iostream>
#include <string>
#include <windows.h>


uint64_t real_string_hash(std::string& S, int& p, int& n) {
    uint64_t hash = 0;
    int power = 1; // p^0 = 1
    for (unsigned char c : S) {
        hash += static_cast<int>(c) * power;    // Умножаем код символа на p^i и добавляем к хешу
        power = (power * p) ;                   // Обновляем степень p
    }
    hash %= n; // Берём остаток
    return hash;
}

// Проверка на простое число
bool is_prime(int& p) {
    for (int i = 2; i <= std::sqrt(p); ++i) {
        if (p % i == 0)     return false;
    }
    return true;
}

// ГЛАВНАЯ ПРОГРАММА
int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string input;
    int hash;
    int p;
    int n;

    std::cout << "Программа рассчета хэша для строки с помощью серьёзного алгоритма" << std::endl;
    std::cout << "Для выхода из программы введите строку: exit" << std::endl << std::endl;

    while (true) {
        std::cout << "Введите простое число p: ";

        std::cin >> p;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (is_prime(p) == true)
            break;
        else
            std::cout << "Ошибка. Число p=" << p << " не является простым!" << std::endl;
    }

    while (true) {
        std::cout << "Введите модуль n: ";

        std::cin >> n;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (n != 0)
            break;
        else
            std::cout << "Ошибка. Число n должно быть не равно 0." << std::endl;
    }

    while (true) {
        
        std::cout << "Введите строку: ";        
        // Чтение всей строки включая пробелы
        if (!std::getline(std::cin >> std::ws, input)) {
            // Ошибка ввода (например, Ctrl+Z/Ctrl+D)
            std::cin.clear(); // Сброс флагов ошибок
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
            std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;
            
            continue;
        }

        // Вычисляем хэш
        std::cout << "Хэш строки " << input << " = " << real_string_hash(input, p, n) << std::endl;

        if (input == "exit") {
            break;
        }
    }

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

