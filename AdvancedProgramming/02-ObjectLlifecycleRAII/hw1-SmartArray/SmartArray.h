#pragma once

#include <iostream>
#include <stdexcept>

class SmartArray {
private:
    int* FData;             // Указатель на массив
    int FActualSize;        // Количество элементов под которое выделена память
    int FLogicalSize;       // Фактическое количество элементов   

    int at(int index);      // Получить элемент по индексу с проверкой
public:  
    SmartArray(int size);   // Конструктор
    ~SmartArray();          // Деструктор

    int ActualSize();       // Количество элементов под которое выделена память
    int LogicalSize();      // Фактическое количество элементов   
    
    void add_element(int value); // Добавление элемента (с динамическим расширением)

    // Перегрузка оператора [] для удобства
    int& operator[](size_t index) {
        return const_cast<int&>(static_cast<const SmartArray&>(*this).at(index));
    }
};

// Пример использования
int main() {
    
    
    
    //SmartArray arr(3); // Создаем массив на 3 элемента

    //// Добавляем элементы (массив сам расширится)
    //for (int i = 0; i < 10; ++i) {
    //    arr.push_back(i * 10);
    //}

    //// Получаем элементы
    //for (size_t i = 0; i < arr.size(); ++i) {
    //    std::cout << arr[i] << " "; // Используем operator[]
    //}

    //// Проверка обработки ошибок
    //try {
    //    std::cout << "\nElement at 100: " << arr.at(100);
    //}
    //catch (const std::out_of_range& e) {
    //    std::cerr << "\nError: " << e.what();
    //}
    

    system("pause");

    return EXIT_SUCCESS;
}
