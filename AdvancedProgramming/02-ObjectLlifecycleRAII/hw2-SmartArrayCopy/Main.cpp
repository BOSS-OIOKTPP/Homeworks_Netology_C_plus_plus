#include <iostream>
#include "SmartArrayNew.h"
#include <windows.h>

// Пример использования
int main() {

	// Установка кодировки консоли Windows
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	SmartArray arr(5);
	SmartArray new_array(2);
	try {		
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		
		new_array.add_element(44);
		new_array.add_element(34);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	// Печать массива 1
	std::cout << "Массив 1: " << arr.Print() << std::endl;
	// Печать массива 2
	std::cout << "Массив 2: " << new_array.Print() << std::endl << std::endl;

	// Копируем	
	arr = new_array;

	// Массив 1 после копирования
	std::cout << "Массив 1 = Массив 2" << std::endl << std::endl;
	std::cout << "Массив 1: " << arr.Print() << std::endl << std::endl;
	
	//// Копируем	
	//new_array = arr;

	//// Массив 1 после копирования
	//std::cout << "Массив 2 = Массив 1" << std::endl << std::endl;
	//std::cout << "Массив 2: " << new_array.Print() << std::endl << std::endl;



    system("pause");

    return EXIT_SUCCESS;
}
