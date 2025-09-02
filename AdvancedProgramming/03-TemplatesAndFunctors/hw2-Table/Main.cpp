#include <iostream>
#include <windows.h>
#include "Table.h"



// Пример использования
int main() {

    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    auto test = Table<int>(2, 3);
    test[0][0] = 4; test[0][1] = 0; test[0][2] = 0;
    test[1][0] = 0; test[1][1] = 0; test[1][2] = 0;

    test.Print();
    std::cout << "Размер массива: " << test.Size() << std::endl;
    std::cout << "Элемент [0; 0] = " << test[0][0] << std::endl;

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
