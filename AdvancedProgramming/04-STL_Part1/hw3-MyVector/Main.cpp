#include <iostream>
#include <windows.h>
#include "Vector.h"


int main() {
    // Установили кодировку
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        Vector<int> input{ 1,5,1,3,4,4 };

        // Выводим на экран входные данные
        std::cout << "Динамический массив: " << input.Print_Vector() << std::endl;
        std::cout << "Элемент[0] = " << input.At(0) << std::endl;
        std::cout << "Элемент[1] = " << input.At(1) << std::endl;
        std::cout << "Элемент[2] = " << input.At(2) << std::endl;
        std::cout << "Элемент[3] = " << input.At(3) << std::endl;
        std::cout << "Элемент[4] = " << input.At(4) << std::endl;
        std::cout << "Элемент[5] = " << input.At(5) << std::endl;

        std::cout << "Элемент[6] = " << input.At(6) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
