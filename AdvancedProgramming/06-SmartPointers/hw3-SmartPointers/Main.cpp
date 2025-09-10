#include <iostream>
#include <Windows.h>

template<typename T>
class unique_ptr {
private:
    T* ptr;  // Сырой указатель
public:
    // Конструктор
    unique_ptr(T* p = nullptr): ptr(p) {}

    // Запрещаем конструктор копирования
    unique_ptr(const unique_ptr&) = delete;

    // Запрещаем оператор присваивания
    unique_ptr& operator=(const unique_ptr&) = delete;

    // Перегружаем оператор *
    T& operator*() const {
        return *ptr;
    }

    // Освобождаем владение и возвращаем сырой указатель
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // Перегружаем оператор для вывода адреса указателя
    friend std::ostream& operator<<(std::ostream& os, const unique_ptr<T>& p) {
        return os << static_cast<void*>(p.ptr);
    }

    // Деструктор
    ~unique_ptr() {
        delete ptr;    
    }
};


// Класс для тестирования
class Test {
public:
    int value;
    Test(int v): value(v) {
        std::cout << "Test(" << value << ") создан" << std::endl;
    }
    ~Test() {
        std::cout << "Test(" << value << ") уничтожен" << std::endl;
    }
};


int main()
{
    // Установили кодировку
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    // Создание unique_ptr
    unique_ptr<Test> ptr1(new Test(12));
    std::cout << std::endl;

    // 1
    std::cout << "Создали указатель на объект Test, " << "ptr1 = " << ptr1 << std::endl;
    std::cout << std::endl;

    // 2
    std::cout << "Доступ к объекту через *" << std::endl;
    std::cout << "*ptr1.Value = " << (*ptr1).value << std::endl;
    std::cout << std::endl;

    // 3
    // Освобождаем владение и возвращаем сырой указатель
    Test* ptr2 = ptr1.release();
    std::cout << "Освобождаем владение и возвращает сырой указатель Test* ptr2 = ptr1.release()" << std::endl;   
    std::cout << "ptr1 = " << ptr1 << std::endl;
    std::cout << "ptr2 = " << ptr2 << std::endl;
    std::cout << std::endl;

    // Удаляем объект вручную
    delete ptr2;



    //std::cout << std::endl;
    //system("pause");

    return EXIT_SUCCESS;
}