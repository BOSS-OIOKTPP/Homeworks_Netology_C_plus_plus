#include <iostream>
#include <string>
#include <windows.h>

// Вычисляем хэш строки
int simple_string_hash(std::string S) {
    int hash{ 0 };
    for (unsigned char c : S) {
        hash += static_cast<int>(c); // Суммируем коды символов
    }
    return hash;
}


// ГЛАВНАЯ ПРОГРАММА
int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string input;
    int hash;

    std::cout << "Программа рассчета хэша для строки с помощью наивного алгоритма" << std::endl;
    std::cout << "Для выхода из программы введите строку: exit" << std::endl << std::endl;

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

        if (input == "exit") {
            break;
        }

        // Вычисляем хэш
        std::cout << "Наивный хэш строки " << input << " = " << simple_string_hash(input) << std::endl;
    }

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

