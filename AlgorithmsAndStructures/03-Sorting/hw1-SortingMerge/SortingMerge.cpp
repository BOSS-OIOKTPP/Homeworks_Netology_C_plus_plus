#include <iostream>
#include <string>
#include <windows.h>


// Слияние двух отсортированных массивов
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные массивы
    int* L = new int[n1];
    int* R = new int[n2];

    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Выполняем слияние двух сортированных массивов
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы L[], если они остались
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы R[], если они остались
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Освобождаем память
    delete[] L;
    delete[] R;
}



void merge_sort(int* arr, int size) {


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
    std::cout << "Отсортированный массив 1: ";
    print_array(arr1, size1);
    std::cout << std::endl;

    std::cout << "Исходный массив 2: ";
    print_array(arr2, size2);
    merge_sort(arr2, size2);
    std::cout << "Отсортированный массив 2: ";
    print_array(arr2, size2);
    std::cout << std::endl;

    std::cout << "\nИсходный массив 3: ";
    print_array(arr3, size3);
    merge_sort(arr3, size3);
    std::cout << "Отсортированный массив 3: ";
    print_array(arr3, size3);
    std::cout << std::endl;


    std::cout << std::endl;
    std::cout << "Нажмите любую клавишу для завершения программы." << std::endl;
    std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

