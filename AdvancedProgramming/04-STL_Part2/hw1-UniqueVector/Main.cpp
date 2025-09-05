#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

template<typename T>
void UniqueVector(std::vector<T>& arr) {
    // 1. Выполняем сортировку по возрастанию
    std::sort(arr.begin(), arr.end(),
        [](const auto& a, const auto& b) {
            return a < b;
        });

    // 2. Делаем уникальными числа
    auto it = std::unique(arr.begin(), arr.end());

    // 3. Удаляем элементы, которые остались после применения std::unique
    arr.erase(it, arr.end());    
}

int main() {
    // Установили кодировку
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // 1. Выводим на экран входные данные
    std::vector<int> input{ 1, 1, 2, 5, 6, 1, 2, 4 };
    std::cout << "[IN]: ";
    for (const int& v : input)
        std::cout << v << " ";
    std::cout << std::endl;

    // 2. Делаем уникальный список, отсортированный по возрастанию
    UniqueVector(input);

    // 3. Выводим на печать результат    
    std::cout << "[OUT]: ";
    for (const int& v : input)
        std::cout << v << " ";


    std::cout << std::endl << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
