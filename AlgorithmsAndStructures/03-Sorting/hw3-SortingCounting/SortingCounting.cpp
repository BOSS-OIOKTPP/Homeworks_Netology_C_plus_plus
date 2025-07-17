#include <iostream>
#include <string>
#include <windows.h>



void quick_sort(int* arr, int L, int R) {
    // Выход из рекурсии
    if (L > R) return;

    int p = arr[(L + R) / 2];   // опорное значение запоминаем посередине массива
    int i = L;                  // начальное значение индекса при движении по массиву слева направо
    int j = R;                  // начальное значение индекса при движении по массиву справа налево
    while (i <= j) {
        while (arr[i] < p) i++;     // ищим значение массива больше или равно p двигаясь по массиву от левой границы
        while (arr[j] > p) j--;     // ищим значение массива меньше или равно p двигаясь по массиву от правой границы
        //
        if (i <= j) {
            // меняем местами эти значения
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            // индекс i на шаг увеличиваем
            i++;
            // индекс j на шаг уменьшаем
            j--;
        }
    }
    // После цикла j < i
    // запускаем рекурсивно сортировку по левой части массива
    quick_sort(arr, L, j);
    // запускаем рекурсивно сортировку по правой части массива
    quick_sort(arr, L, j);
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
    quick_sort(arr1, 0,size1-1);
    std::cout << std::endl;
    std::cout << "Отсортированный массив 1: ";
    print_array(arr1, size1);
    std::cout << std::endl << std::endl;


    std::cout << "Исходный массив 2: ";
    print_array(arr2, size2);
    quick_sort(arr2, 0, size2 - 1);
    std::cout << std::endl;
    std::cout << "Отсортированный массив 2: ";
    print_array(arr2, size2);
    std::cout << std::endl << std::endl;

    std::cout << "Исходный массив 3: ";
    print_array(arr3, size3);
    quick_sort(arr3, 0, size3 - 1);
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
