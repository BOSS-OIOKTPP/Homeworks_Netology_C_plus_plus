#include <iostream>
#include <windows.h>

int main(int argc, char** argv)
{
	// ������������� ��������� ������� � UTF-8
	 // ��������� ��������� ������� Windows
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string Name;

	std::cout << "������� ��� : ";
	std::cin >> Name;


	std::cout << "������������, " << Name << "!" << std::endl;

	return EXIT_SUCCESS;
}