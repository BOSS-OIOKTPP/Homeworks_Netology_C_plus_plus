#include <iostream>
#include <windows.h>

int main(int argc, char** argv)
{
	// ������������� ��������� ������� � UTF-8
	 // ��������� ��������� ������� Windows
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string name;

	std::cout << "������� ��� : ";
	std::cin >> name;


	std::cout << "������������, " << name << "!" << std::endl;

	return EXIT_SUCCESS;
}