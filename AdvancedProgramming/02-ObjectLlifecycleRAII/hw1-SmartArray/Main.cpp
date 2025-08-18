#include <iostream>
#include "SmartArray.h"
#include <windows.h>

// Пример использования
int main() {

	// Установка кодировки консоли Windows
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try {
		SmartArray arr(5);

		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);

		std::cout << arr[0] << std::endl;
		std::cout << arr[1] << std::endl;
		std::cout << arr[2] << std::endl;
		std::cout << arr[3] << std::endl;
		std::cout << arr[4] << std::endl;

		std::cout << arr[5] << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}


    system("pause");

    return EXIT_SUCCESS;
}
