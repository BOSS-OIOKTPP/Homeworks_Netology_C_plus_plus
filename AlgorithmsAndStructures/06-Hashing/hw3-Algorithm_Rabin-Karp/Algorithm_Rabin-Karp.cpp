#include <iostream>
#include <string>
#include <windows.h>


// Вычисляем хэш строки
int simple_string_hash(std::string& S, int start, int length) {
    int hash{ 0 };
    for (int i = 0; i < length; ++i) {
        unsigned char c;
        c = S[i];
        hash += static_cast<int>(c); // Суммируем коды символов
    }
    return hash;
}

// Выполняем поиск
int find_substring_light_rabin_karp(std::string& text, std::string& pattern) {
    int pattern_length  = static_cast<int>(pattern.size());
    int text_length     = static_cast<int>(text.size());
    int pattern_hash    = simple_string_hash(pattern, 0, pattern_length);

    for (int i = 0; i <= text_length - pattern_length; ++i) {
        int current_hash = simple_string_hash(text, i, pattern_length);
        if (current_hash == pattern_hash) {
            // Дополнительная проверка на случай коллизии, сравниваем посимвольно
            bool match = true;
            for (int j = 0; j < pattern_length; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match==true) {
                return i;
            }
        }
    }
    return -1;
}



// ГЛАВНАЯ ПРОГРАММА
int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string text;
    std::string pattern;
    int index;
    

    std::cout << "Программа поиска подстроки в заданной строке с помощью упрощённого алгоритма Рабина-Карпа" << std::endl << std::endl;
    std::cout << "Для выхода из программы введите строку: exit" << std::endl << std::endl;

    while (true) {
        std::cout << "Введите строку, в которой будет осуществляться поиск: ";
        // Чтение всей строки включая пробелы
        if (!std::getline(std::cin >> std::ws, text)) {
            // Ошибка ввода (например, Ctrl+Z/Ctrl+D)
            std::cin.clear(); // Сброс флагов ошибок
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
            std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;

            continue;
        }
        break;
    }

    while (true) {

        while (true) {
            std::cout << "Введите подстроку, которую нужно найти: ";
            // Чтение всей строки включая пробелы
            if (!std::getline(std::cin >> std::ws, pattern)) {
                // Ошибка ввода (например, Ctrl+Z/Ctrl+D)
                std::cin.clear(); // Сброс флагов ошибок
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
                std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;

                continue;
            }
            break;
        }

        if (pattern == "exit") {
            break;
        }

        // выполняем поиск
        index = find_substring_light_rabin_karp(text, pattern);        
        if (index==-1) 
            std::cout << "Подстрока " << pattern << " не найдена" << std::endl;
        else
            std::cout << "Подстрока " << pattern << " найдена по индексу " << index << std::endl;

    }

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

