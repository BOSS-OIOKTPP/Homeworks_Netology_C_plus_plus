#include <iostream>
#include <windows.h>
#include <future>
#include <vector>
#include <iomanip>

const int width_N  = 25;
const int width_N2 = 5;

// Рекурсивная функция  (границы в С++ для итераторов: левая принадлежит диапазону, правая нет - [first, last)  )
void for_each(auto first, auto last, auto func, int level);

// Функция для вывода массива
void printArray(std::vector<int>& arr, std::string mes);



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Параллельная обработка массива" << std::endl;
    std::cout << std::endl;

    std::vector<int> test_data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    std::cout << std::setw(width_N) << std::left << "Исходные данные: ";
    printArray(test_data, "");
    std::cout << std::endl << std::endl;

    // Тест 1: Умножение каждого элемента на 2
    for_each(test_data.begin(), test_data.end(), [](int& x) { x *= 2; });
    std::cout << std::setw(width_N) << std::left << "После умножения на 2: ";
    printArray(test_data, "");
    std::cout << std::endl << std::endl;

    // Тест 2: Прибавление 10 к каждому элементу
    for_each(test_data.begin(), test_data.end(), [](int& x) { x += 10; });
    std::cout << std::setw(width_N) << std::left << "После прибавления 10: ";
    printArray(test_data, "");
    std::cout << std::endl << std::endl;

    // Тест 3: Вывод элементов
    std::cout << std::setw(width_N) << std::left << "Вывод через for_each: ";
    for_each(test_data.begin(), test_data.end(), [](int& x) {
        std::cout << std::setw(width_N2) << std::left << x;
        });
    std::cout << std::endl << std::endl;
    


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}



// Рекурсивная функция  (границы в С++ для итераторов: левая принадлежит диапазону, правая нет - [first, last)  )
void for_each(auto first, auto last, auto func, int level = 0) {
    // определяем интервал
    size_t distance = std::distance(first, last);

    // Добавим ограничения на создание потоков
    // Если полученный интервал меньше 5 или уровень рекурсии больше 4, то 
    // обрабатываем последовательно
    if (distance < 5 || level > 3) { 
        std::for_each(first, last, func);
        return;
    }

    // Иначе делим диапазон пополам    
    auto first1 = first; auto last1 = first; std::advance(last1, distance / 2);    // 1 часть    [first1, last1)
    auto first2 = last1; auto last2 = last;                                        // 2 часть    [first2, last2) 

    // Запускаем асинхронно
    auto future1 = std::async(std::launch::async, for_each, first1, last1, func, level + 1);  // 1 часть
    auto future2 = std::async(std::launch::async, for_each, first2, last2, func, level + 1);  // 2 часть
    
    // Ждем завершения
    future1.get();   // 1 части    
    future2.get();   // 2 части
}

// Функция для вывода массива
void printArray(std::vector<int>& arr, std::string mes) {
    std::cout << mes;
    for (size_t i = 0; i < arr.size(); ++i) 
        std::cout << std::setw(width_N2) << std::left << arr[i];
}