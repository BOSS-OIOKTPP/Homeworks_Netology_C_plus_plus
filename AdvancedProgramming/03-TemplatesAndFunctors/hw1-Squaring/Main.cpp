#include <iostream>
#include <string>
#include <windows.h>

// Пример использования
int main() {

    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string input;

    while (true) {
        // Очищаем консоль 
        system("cls");

        std::cout << "Введите числа, отделяя их пробелами" << std::endl;

        // Чтение всей строки
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

        
    }

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
