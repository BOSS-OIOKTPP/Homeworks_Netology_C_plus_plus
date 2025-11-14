#include <iostream>
#include <windows.h>
#include <future>
#include <string>
#include <chrono>
#include <vector>


struct MinResult {
    int index;                                              // Индекс минимального элемента
    int value;                                              // Значение минимального элемента    
    MinResult(int idx, int val) : index(idx), value(val) {} // Конструктор
};

// Функция для поиска минимального элемента в части массива
MinResult findMinResult(std::vector<int>& arr, int start);

// Функция сортировки выбором. Поиск минимального элемента выполняется в параллельном потоке std::async
void SortAsync2(std::vector<int>& arr, std::promise<MinResult> prom);

// Функция для вывода массива
void printArray(std::vector<int>& arr, std::string mes);



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Тестовые данные
    std::vector<int> data = { 64, 25, 12, 22, 11, 5, 8, 3, 10, 1 };
    printArray(data, "Исходный массив data[]: ");

    std::promise<MinResult> prom;
    std::future<MinResult> res = prom.get_future();
    auto R = std::async(std::launch::async, SortAsync2, std::ref(data), move(prom));

    // Ждем завершения и получаем результат
    MinResult min = res.get();    
    std::cout << "\nМинимальный элемент data[" << min.index << "] = " << min.value << std::endl;

    // Т.к. поиск минимального значения получит результат раньше чем выполнится сортировка, то 
    // необходимо подождать завершение потока
    R.wait();

    printArray(data, "\nОтсортированный массив data[]: ");
    std::cout << std::endl;

    
    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}



// Функция для поиска минимального элемента в части массива
MinResult findMinResult(std::vector<int>& arr, int start) {
    MinResult t(start, arr[start]);
    for (int i = start + 1; i < arr.size(); ++i) {
        if (arr[i] < t.value) {
            t.index = i;
            t.value = arr[i];
        }
    }
    return t;
}

// Функция сортировки выбором. Поиск минимального элемента выполняется в параллельном потоке std::async
void SortAsync2(std::vector<int>& arr, std::promise<MinResult> prom) {
    int n = arr.size();
    MinResult res{ -1,0 };
    for (int i = 0; i < n - 1; ++i) {
        // запускаем поиск в потоке
        std::future<MinResult> f = std::async(std::launch::async, findMinResult, std::ref(arr), i);
        // Ждем значение
        res = f.get();
        // Обмениваем элементы
        if (res.index != i)
            std::swap(arr[i], arr[res.index]);

        // Передаем результат - это минимальное значение
        if (i == 0)
            prom.set_value(res);
    }    
}

// Функция для вывода массива
void printArray(std::vector<int>& arr, std::string mes) {
    std::cout << mes;
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i < arr.size() - 1) 
            std::cout << " ";        
    }
    std::cout << std::endl;
}
