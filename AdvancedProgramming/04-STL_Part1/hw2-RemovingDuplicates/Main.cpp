#include <iostream>
#include <windows.h>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include "InputNumbers.h"


int main() {
    // Установили кодировку
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    // Входные данные - ВАРИАНТ 1 
    int input_count{ 6 };
    std::vector<int> input{ 1, 5, 1, 3, 4, 4 };   
    

    // Входные данные - ВАРИАНТ 2 
    //int input_count{ 0 };
    //std::vector<int> input;
    //InputNumbers(input_count, input);    
    //system("cls");  // Очищаем консоль 



    // 1. Выводим на экран входные данные
    std::cout << "[IN]: " << std::endl;
    std::cout << input_count << std::endl;
    for (const int& v : input)
        std::cout << v << std::endl;

    // 2. Запиcываем входные данные в множество
    std::set<int> my_set;
    for (const int& v : input) my_set.insert(v); 

    // 3. Выводим на печать в обратном порядке (т.к. в множестве уже порядок по возрастанию)    
    std::cout << "[OUT]: " << std::endl;
    for (auto p = my_set.rbegin(); p != my_set.rend(); ++p) 
        std::cout << *p << std::endl;
    



    //****************************************//
    //         РЕШЕНИЕ 2                      //
    // ПО АНАЛОГИИ КАК В ПЕРВОМ ЗАДАНИИ       //
    //   hw1-CharacterFrequency               //
    //****************************************//
    
    //// 1. Подсчитали частоту символов, при этом получим уникальный список
    //std::map<int, int> freq;
    //for (int i : input) freq[i]++;

    //// 2. Копируем пары чисел в вектор     
    //std::vector<std::pair<int, int>> sorted(freq.begin(), freq.end());

    //// 3. Выполняем сортировку
    //std::sort(sorted.begin(), sorted.end(),
    //    // по убыванию чисел
    //    [](const auto& a, const auto& b) {
    //        return a.first > b.first; 
    //    });

    //// 4. Выводим результат
    //std::cout << "[OUT]: " << std::endl;
    //for (const auto& p : sorted) 
    //    std::cout << p.first << std::endl;
    


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
