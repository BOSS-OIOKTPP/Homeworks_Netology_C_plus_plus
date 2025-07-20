#include <iostream>
#include <string>
#include <windows.h>



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
        if (logical_size > 0 && logical_size <= actual_size) break;

        if (logical_size > actual_size) {
            std::cout << "Ошибка! Логический размер массива не может превышать фактический!" << std::endl << std::endl;
        }

        if (logical_size <= 0) {
            std::cout << "Ошибка! Логический размер массива не может быть меньше 1!" << std::endl << std::endl;
        }
    }

    // Создаем массив
    arr = new int[logical_size];

    // Вводим новые значения
    for (int i = 0; i < logical_size; ++i) {
        std::cout << "Введите arr[" << i << "]: ";
        std::cin >> arr[i];
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
    }

    // Выводим на экран результат
    std::cout << "Динамический массив :";        
    for (int i = 0; i < logical_size; ++i)              std::cout << arr[i] << " ";
    for (int i = logical_size; i < actual_size; ++i)    std::cout << "_" << " ";
       
    // Удаляем массив
    delete[] arr;
 

    std::cout << std::endl;
    //std::cout << "Нажмите любую клавишу для завершения программы." << std::endl;
    std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

