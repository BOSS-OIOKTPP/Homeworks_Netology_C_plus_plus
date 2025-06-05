#include <iostream>
#include <windows.h>

int main(int argc, char** argv)
{
	// Устанавливаем кодировку консоли в UTF-8
	 // Установка кодировки консоли Windows
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string name;

	std::cout << "Введите имя : ";
	std::cin >> name;


	std::cout << "Здравствуйте, " << name << "!" << std::endl;

	return EXIT_SUCCESS;
}