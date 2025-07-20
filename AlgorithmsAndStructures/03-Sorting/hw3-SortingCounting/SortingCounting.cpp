#include <iostream>
#include <string>
#include <windows.h>

// Находим минимальное значение массива
int arr_min(const int* arr, int size) {
    int min_val = arr[0]; 
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i]; 
        }
    }
    return min_val;
}

// Находим максимальное значение массива
int arr_max(const int* arr, int size) {
    int max_val = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}


void count_sort(int* arr, int size) {
    const int min_val = arr_min(arr, size);
    const int max_val = arr_max(arr, size);
    const int range = max_val - min_val + 1;

    // Создаем массив для подсчета количества повторений чисел в массиве arr
    // Сами значения массива arr будут частью индексов массива count, значения будут содержать количество повторений
    int* count = new int[range]();

    // Подсчитываем количество каждого элемента в массиве arr и записываем в count
    for (int i = 0; i < size; ++i) {
        int idx = arr[i] - min_val;     // индекс для массива count
        count[idx]++;                   // увеличиваем значение на единицу
    }

    // т.к. мы использовали значения из массива arr как индексы в массиве count, то теперь мы можем 
    // совершить обратную операцию - заполнить массив arr уже в отсортированном порядке  
    // не забываем добавить min_val к индексу массива count, т.к. мы делали преобразование значения массива arr в индексы массива count выше 
    int i = 0;
    for (int idx = 0; idx < range; ++idx) {
        // повторяем столько раз сколько записано в count        
        while (count[idx] > 0) {            
            arr[i] = min_val + idx;
            i++; 
            count[idx]--;
        }
    }
}

// Печатаем массив
void print_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
}


// ГЛАВНАЯ ПРОГРАММА
int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Исходные данные
    // Тестовые массивы
    int arr1[] = { 19, 14, 22, 22, 17, 22, 13, 21, 20, 24, 18, 10, 17, 16, 17, 20, 22, 11, 20, 16, 14, 13, 10, 22, 18, 14, 16, 24, 19, 17 };
    int arr2[] = { 16, 17, 14, 20, 22, 20, 17, 22, 16, 19, 23, 24, 20, 22, 21, 18, 14, 16, 17, 21, 10, 11, 19, 23, 11, 11, 17, 17, 11, 21, 17, 11, 17, 16, 12, 11, 16, 22, 23, 16 };
    int arr3[] = { 21, 15, 19, 18, 23, 12, 18, 18, 19, 23, 12, 20, 15, 22, 21, 18, 19, 20, 12, 16, 20, 14, 17, 13, 10, 23, 19, 14, 10, 22, 19, 12, 24, 23, 22, 15, 13, 22, 18, 18, 11, 23, 24, 17, 10 };
                   
    // Размеры массивов
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    // Сортировка и вывод результатов
    std::cout << "Исходный массив 1: ";
    print_array(arr1, size1);
    count_sort(arr1, size1);
    std::cout << std::endl;
    std::cout << "Отсортированный массив 1: ";
    print_array(arr1, size1);
    std::cout << std::endl << std::endl;


    std::cout << "Исходный массив 2: ";
    print_array(arr2, size2);
    count_sort(arr2, size2);
    std::cout << std::endl;
    std::cout << "Отсортированный массив 2: ";
    print_array(arr2, size2);
    std::cout << std::endl << std::endl;

    std::cout << "Исходный массив 3: ";
    print_array(arr3, size3);
    count_sort(arr3, size3);
    std::cout << std::endl;
    std::cout << "Отсортированный массив 3: ";
    print_array(arr3, size3);
    std::cout << std::endl << std::endl;

    //std::cout << std::endl;
    //std::cout << "Нажмите любую клавишу для завершения программы." << std::endl;
    //std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}
