#pragma once
#include <iostream>
#include <vector>

void InputNumbers(int& input_count, std::vector<int>& input) {
    while (true) {
        std::cout << "Введите количество чисел для анализа: ";
        std::cin >> input_count;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
        if (input_count > 0) break;
        else
            std::cout << "Ошибка! Значение должно быть больше нуля!" << std::endl << std::endl;
    }

    // Вводим новые значения    
    int i = 0;
    while (i < input_count) {
        int tmp{ 0 };
        std::cout << "Введите значение[" << i << "]: ";
        std::cin >> tmp;
        if (!std::cin) {
            std::cout << "Ошибка! Введите целое число!" << std::endl;
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки            
            continue;
        }
        input.push_back(tmp);
        i++;
    }
}
