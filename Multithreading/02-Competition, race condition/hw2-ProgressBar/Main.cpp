#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>


const int MAX_THREADS = 5;
const int CALC_COUNT = 1000;
/*
void func1()
{
	std::cout << "#id = " << std::this_thread::get_id() << std::endl;
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(100ms);
		consol_color::SetColor(15, 0);
		cout << i << " ";
	}
	cout << endl;
}

void func2()
{
	cout << "#id = " << this_thread::get_id() << endl;
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(100ms);
		consol_color::SetColor(10, 0);
		cout << i << " ";
	}
	cout << endl;
}
*/

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void SetPosition(int x, int y)
{
	COORD point;
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(hStdOut, point);
}

// Имитация расчета
void calculate(int num_thread) {
	int x{ 0 };
	for (int i = 0; i < CALC_COUNT; ++i) {
		x = x + std::rand();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		int percent = static_cast<double>(i / CALC_COUNT) * 100.0;


		
	}
}





int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	// Инициализируем генератор случайных чисел, чтобы при каждом запуске генерировались разные числа
	std::srand(static_cast<unsigned int>(std::time(nullptr)));


	std::thread* t = new std::thread[5];
	for (int i=0; i< MAX_THREADS; ++i)
		t[i] = std::thread()


    
//	std::cout << "#id = " << std::this_thread::get_id() << std::endl;
//	for (int i = 0; i < 10; i++)

	
	//std::cout << "Начало работы. Максимальное количество клиентов: " << MAX_CLIENTS << std::endl << std::endl << std::endl;

 //   std::cout << "ТЕСТ 1: Доступа к памяти: Последовательное согласование - memory_order_seq_cst" << std::endl << std::endl;
 //   std::thread clientThread1(clientProcess_SegCst);
 //   std::thread operatorThread1(operatorProcess_SegCst);
 //   clientThread1.join();    // Ждем завершение потока
 //   operatorThread1.join();  // Ждем завершение потока  
 //   std::cout << std::endl << std::endl << std::endl;





    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

