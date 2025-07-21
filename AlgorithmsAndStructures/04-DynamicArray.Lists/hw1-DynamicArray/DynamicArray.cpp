#include <iostream>
#include <string>
#include <windows.h>

void print_dynamic_array(int* arr, int logical_size, int actual_size) {
    for (int i = 0; i < logical_size; ++i)              std::cout << arr[i] << " ";
    for (int i = logical_size; i < actual_size; ++i)    std::cout << "_" << " ";
}

// ГЛАВНАЯ ПРОГРАММА
int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int actual_size{ 0 };
    int logical_size{ 0 };
    int* arr;

    while (true) {
        // Очищаем консоль 
        system("cls");

        std::cout << "Введите фактичеcкий размер массива: ";
        std::cin >> actual_size;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (actual_size > 0 ) break;
    }

    while (true) {
        std::cout << "Введите логичеcкий размер массива: ";
        std::cin >> logical_size;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
        if (logical_size >= 0 && logical_size <= actual_size) break;

        if (logical_size > actual_size) {
            std::cout << "Ошибка! Логический размер массива не может превышать фактический!" << std::endl << std::endl;
        }

        if (logical_size < 0) {
            std::cout << "Ошибка! Логический размер массива не может быть меньше 0!" << std::endl << std::endl;
        }
    }

    // Создаем массив
    arr = new int[actual_size];

    // Вводим новые значения
    int i = 0;
    while (i < logical_size) {
        int tmp{ 0 };
        std::cout << "Введите arr[" << i << "]: ";
        std::cin >> tmp;
        if (!std::cin) {
            std::cout << "Ошибка! Введите целое число!" << std::endl;
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки            
            continue;
        }
        arr[i] = tmp;
        i++;
    }

    // Выводим на экран результат
    std::cout << "Динамический массив :";        
    print_dynamic_array(arr, logical_size, actual_size);
    std::cout << std::endl;

       
    // Удаляем массив
    delete[] arr;
 

    std::cout << std::endl;
    //std::cout << "Нажмите любую клавишу для завершения программы." << std::endl;
    std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

