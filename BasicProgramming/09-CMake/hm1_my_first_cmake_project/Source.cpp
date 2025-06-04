#include <iostream>
#include <windows.h>

int main(int argc, char** argv)
{
	// Устанавливаем кодировку консоли в UTF-8
	 // Установка кодировки консоли Windows
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string Name;

	std::cout << "Введите имя : ";
	std::cin >> Name;


	std::cout << "Здравствуйте, " << Name << "!" << std::endl;

	return EXIT_SUCCESS;
}