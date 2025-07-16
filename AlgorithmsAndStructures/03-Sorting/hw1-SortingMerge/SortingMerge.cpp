#include <iostream>
#include <string>
#include <windows.h>


// Слияние двух отсортированных массивов
// int* arr     - исходный массив, куда запишем отсортированные значения
// int* L       - левая часть исходного массива 
// int size_L   - размер левого массива
// int* R       - правая часть исходного массива
// int size_R   - размер правого массива
void merge(int* arr, int* L, int size_L, int* R, int size_R) {
    int i = 0;
    int j = 0;
    int k = 0;
    
    // Пока не вышли за размер левого или правого массива проводим сравнение
    while (i < size_L && j < size_R) {
        if (L[i] <= R[j])   { 
            arr[k] = L[i]; i++; 
        }
        else { 
            arr[k] = R[j]; j++; 
        }
        k++;
    }

    // Копируем оставшиеся элементы L[], если они остались
    while (i < size_L) { arr[k] = L[i]; i++; k++; }
    // или копируем оставшиеся элементы R[], если они остались
    while (j < size_R) { arr[k] = R[j]; j++; k++; }
}


void merge_sort(int* arr, int size) {
    // Если размер массива равен 1, то выходим
    if (size == 1) return;

    // разбиваем массив на 2 части
    int size_L = size / 2;          // размер левой части
    int size_R = size - size_L;     // размер правой части

    // Создаем временные массивы
    int* L = new int[size_L];
    int* R = new int[size_R];

    // Копируем данные во временные массивы
    for (int i = 0; i < size_L; i++) { L[i] = arr[i]; }
    for (int j = 0; j < size_R; j++) { R[j] = arr[size_L + j]; }

    // Сортируем левую и правую части
    merge_sort(L, size_L);
    merge_sort(R, size_R);

    // Сливаем отсортированные половины
    merge(arr, L, size_L, R, size_R);
    
    // Освобождаем память
    delete[] L;
    delete[] R;
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
    int arr1[] = { 3, 43, 38, 29, 18, 72, 57, 61, 2, 33 };
    int arr2[] = { 88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74 };
    int arr3[] = { 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62 };

    // Размеры массивов
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    // Сортировка и вывод результатов
    std::cout << "Исходный массив 1: ";
    print_array(arr1, size1);
    merge_sort(arr1, size1);
    std::cout << std::endl;
    std::cout << "Отсортированный массив 1: ";
    print_array(arr1, size1);
    std::cout << std::endl << std::endl;


    std::cout << "Исходный массив 2: ";
    print_array(arr2, size2);
    merge_sort(arr2, size2);
    std::cout << std::endl;
    std::cout << "Отсортированный массив 2: ";
    print_array(arr2, size2);
    std::cout << std::endl << std::endl;

    std::cout << "Исходный массив 3: ";
    print_array(arr3, size3);
    merge_sort(arr3, size3);
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

