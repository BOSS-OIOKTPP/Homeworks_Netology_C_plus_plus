#include <iostream>
#include <windows.h>
#include <future>
#include <string>
#include <vector>



// Функция для вывода массива
void printArray(std::vector<int>& arr, std::string mes);

//
void for_each(auto first, auto last, auto func, int depth);


int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Тестовые данные
    std::vector<int> data = { 64, 25, 12, 22, 11, 5, 8, 3, 10, 1 };
    printArray(data, "Исходный массив data[]: ");

    std::promise<MinResult> prom;
    std::future<MinResult> res = prom.get_future();
    //auto R = std::async(SortAsync, std::ref(data), move(prom));     // вариант 1
    auto R = std::async(SortAsync2, std::ref(data), move(prom));      // вариант 2 - с std::async(findMinResult)

    // Ждем завершения и получаем результат
    MinResult min = res.get();    

    // Т.к. поиск минимального значения получит результат раньше чем выполнится сортировка, то 
    // необходимо подождать завершение потока
    R.wait();

    printArray(data, "\nОтсортированный массив data[]: ");
    std::cout << std::endl;

    std::cout << "Минимальный элемент data[" << min.index << "] = " << min.value << std::endl;

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}


// Функция для вывода массива
void printArray(std::vector<int>& arr, std::string mes) {
    std::cout << mes;
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i < arr.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void for_each(auto first, auto last, auto func) {
    size_t distance = std::distance(first, last);
    // Если диапазон маленький, т.е. меньше или равен 4 обрабатываем последовательно
    if (distance <= 4) {  
        std::for_each(first, last, func);
        return;
    }

    // Рекурсивный случай: делим диапазон пополам
    auto middle = first;
    std::advance(middle, distance / 2);

    // Запускаем левую половину асинхронно
    auto left_future = std::async(std::launch::async,
        for_each<auto, auto>, first, middle, func, depth + 1);

    // Правую половину обрабатываем в текущем потоке
    parallel_for_each_impl(middle, last, func, depth + 1);

    // Ждем завершения левой половины
    left_future.get();
}
