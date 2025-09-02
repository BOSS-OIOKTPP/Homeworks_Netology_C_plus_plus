#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>



int main() {
    // Установили кодировку
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Входные данные
    std::string input = "Hello world!!";
    std::cout << "[IN]: " << input << std::endl;

    // 1. Подсчитали частоту символов
    std::map<char, int> freq;
    for (char c : input) freq[c]++;

    // 2. Копируем пары чисел в вектор     
    std::vector<std::pair<char, int>> sorted(freq.begin(), freq.end());

    // 3. Выполняем сортировку
    std::sort(sorted.begin(), sorted.end(),
        // по убыванию частоты
        [](const auto& a, const auto& b) {
            return a.second > b.second; 
        });

    // 4. Выводим результат
    std::cout << "[OUT]: " << std::endl;
    for (const auto& p : sorted) 
        std::cout << p.first << ": " << p.second << std::endl;
    


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
