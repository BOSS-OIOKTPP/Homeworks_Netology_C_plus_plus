#include <iostream>
#include <string>
#include <windows.h>

// Вычислим уровень дерева
// Для этого поднимаемся от текущего узла к корню
// Каждая итерация (index - 1) / 2 даёт индекс родителя,
// а каждый подъём к родителю увеличивает уровень на 1
int calculate_level(int index) {
    int level = 0;
    while (index > 0) {
        index = (index - 1) / 2;
        level++;
    }
    return level;
}


void print_pyramid(int* arr, int size) {
    
    if (size==0) {
        std::cout << "Пирамида пуста" << std::endl;
        return;
    }

    // Корневой элемент
    std::cout << "0 root " << arr[0] << std::endl;

    for (int i = 1; i < size; ++i) {
        int level = calculate_level(i);
        int parent_index = (i - 1) / 2;
        int parent_value = arr[parent_index];
        std::string child_type = (i % 2 == 1) ? "left" : "right";

        std::cout << level << " " << child_type << "(" << parent_value << ") " << arr[i] << std::endl;
    }
};

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
    int arr1[] = { 1, 3, 6, 5, 9, 8 };
    int arr2[] = { 94, 67, 18, 44, 55, 12, 6, 42 };
    int arr3[] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4, };

    // Размеры массивов
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    // Сортировка и вывод результатов
    std::cout << "Исходный массив 1: ";
    print_array(arr1, size1);
    std::cout << std::endl;
    std::cout << "Пирамида: " << std::endl;
    print_pyramid(arr1, size1);
    std::cout << std::endl;


    std::cout << "Исходный массив 2: ";
    print_array(arr2, size2);
    std::cout << std::endl;
    std::cout << "Пирамида: " << std::endl;
    print_pyramid(arr2, size2);
    std::cout << std::endl;

    std::cout << "Исходный массив 3: ";
    print_array(arr3, size3);  
    std::cout << std::endl;
    std::cout << "Пирамида: " << std::endl;
    print_pyramid(arr3, size3);
    std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

