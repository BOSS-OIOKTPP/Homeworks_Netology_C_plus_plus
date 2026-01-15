#include <iostream>
#include <windows.h>


int main() {
    // Установка кодировки консоли Windows
    // Установка кодировки консоли Windows
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8); // 65001

    

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

