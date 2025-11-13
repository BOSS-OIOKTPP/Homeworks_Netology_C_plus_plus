#include <iostream>
#include <windows.h>
#include <vector>
#include <future>
#include <thread>
#include <chrono>

// Структура для хранения результатов поиска минимума
struct MinResult {
    int index;                                              // Индекс минимального элемента
    int value;                                              // Значение минимального элемента     
    MinResult(int idx, int val) : index(idx), value(val) {} // Конструктор для удобства
};

// Функция для поиска минимального элемента в части массива
MinResult findMinResult(const std::vector<int>& arr, int start);

// Сортировка выбором с использованием std::async
void SortAsync(std::vector<int>& arr); 

int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Исходные данные
    std::vector<int> data = { 9, 7, 5, 3, 1, 8, 6, 4, 2, 0 };

    std::cout << "Исходный массив: ";
    for (int num : data) std::cout << num << " ";    
    std::cout << std::endl << std::endl;

    // Создаем promise и future для связи между потоками
    std::promise<std::vector<int>> promise;
    std::future<std::vector<int>> future = promise.get_future();

    // Запускаем сортировку асинхронно
    std::async(std::launch::async, SortAsync, std::move(promise), data);

    std::cout << "Основной поток: сортировка запущена, ждем результат..." << std::endl;

    // Получаем отсортированный массив из future (блокируемся до получения результата)
    std::vector<int> sorted_data = future.get();


    std::cout << std::endl << "Отсортированный массив: ";
    for (int num : data) 
        std::cout << num << " ";    
    std::cout << std::endl;


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}


// Функция для поиска минимального элемента в части массива
MinResult findMinIndex(const std::vector<int>& arr, int start) {
    MinResult t(start, arr[start]);
    for (int i = start + 1; i < arr.size(); ++i) {
        if (arr[i] < t.value) {
            t.index = i;
            t.value = arr[i];
        }
    }
    return t;
}

// Сортировка выбором с использованием std::async
void selectionSortAsync(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        // Запускаем асинхронную задачу с помощью std::async
        std::future<std::pair<int, int>> future = std::async(
            std::launch::async, findMinIndex, std::cref(arr), i);

        // Получаем результат из future
        auto [minIndex, minValue] = future.get();

        // Обмениваем элементы
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }

        // Вывод прогресса
        std::cout << "Шаг " << i + 1 << ": ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}