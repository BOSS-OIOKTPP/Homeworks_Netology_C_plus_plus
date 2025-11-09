#include <iostream>
#include <windows.h>
#include <thread>
#include <mutex>
#include <utility>


class Data {
private:
	int value;
	std::mutex mtx;
public:
	Data(int val) : value(val) {}

	int getValue() const { return value; }
	void setValue(int val) { value = val; }

	std::mutex& getMutex() { return mtx; }
	
	void print(const std::string& name) const {
		std::cout << name << ": value = " << value << std::endl;
	}
};

// Вариант 1: std::lock и std::lock_guard
void swap_lock(Data& a, Data& b);
// Вариант 2: std::scoped_lock
void swap_scoped_lock(Data& a, Data& b);
// Вариант 3: std::unique_lock
void swap_unique_lock(Data& a, Data& b);

// Тестовая функция
void test(Data& data1, Data& data2);


int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	Data data1(10);
	Data data2(20);

	std::thread t1(test, std::ref(data1), std::ref(data2));
	t1.join();

	system("pause");

    return EXIT_SUCCESS;
}


// Вариант 1: std::lock и std::lock_guard
void swap_lock(Data& a, Data& b) {
	// Захватываем оба мьютекса
	std::lock(a.getMutex(), b.getMutex());

	// Используем lock_guard (adopt_lock - мьютекс захвачен ранее)
	std::lock_guard<std::mutex> lock_a(a.getMutex(), std::adopt_lock);
	std::lock_guard<std::mutex> lock_b(b.getMutex(), std::adopt_lock);

	// Выполняем обмен данными
	int temp = a.getValue();
	a.setValue(b.getValue());
	b.setValue(temp);
}

// Вариант 2: std::scoped_lock
void swap_scoped_lock(Data& a, Data& b) {
	// Захватываем оба мьютекса
	std::scoped_lock lock(a.getMutex(), b.getMutex());

	// Выполняем обмен данными
	int temp = a.getValue();
	a.setValue(b.getValue());
	b.setValue(temp);
}

// Вариант 3: std::unique_lock
void swap_unique_lock(Data& a, Data& b) {

	// Используем unique_lock (defer_lock - мьютекс будет захвачен позже)
	std::unique_lock<std::mutex> lock_a(a.getMutex(), std::defer_lock);
	std::unique_lock<std::mutex> lock_b(b.getMutex(), std::defer_lock);

	// Захватываем оба мьютекса
	std::lock(lock_a, lock_b);

	// Выполняем обмен данными
	int temp = a.getValue();
	a.setValue(b.getValue());
	b.setValue(temp);
}

// Тестовая функция
void test(Data& data1, Data& data2) {
	std::cout << "Начальные значения:" << std::endl;
	data1.print("data1");
	data2.print("data2");
	std::cout << std::endl;

	// Вариант 1: std::lock и std::lock_guard
	swap_lock(data1, data2);
	std::cout << "После команды swap_lock:" << std::endl;
	data1.print("data1");
	data2.print("data2");
	std::cout << std::endl;

	// Вариант 2: std::scoped_lock
	swap_scoped_lock(data1, data2);
	std::cout << "После команды swap_scoped_lock:" << std::endl;
	data1.print("data1");
	data2.print("data2");
	std::cout << std::endl;

	// Вариант 3: std::swap_unique_lock
	swap_unique_lock(data1, data2);
	std::cout << "После команды swap_unique_lock:" << std::endl;
	data1.print("data1");
	data2.print("data2");
	std::cout << std::endl;
}