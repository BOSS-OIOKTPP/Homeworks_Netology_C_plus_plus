#pragma once
#include <string>

class SmartArray {
private:
    int* FData;             // Указатель на массив
    int FActualSize;        // Количество элементов под которое выделена память
    int FLogicalSize;       // Фактическое количество элементов   
public:  
    SmartArray(int size);           // Конструктор
    ~SmartArray();                  // Деструктор

    int ActualSize() const;         // Количество элементов под которое выделена память
    int LogicalSize() const;        // Фактическое количество элементов   
    
    void add_element(int value);    // Добавление элемента (с динамическим расширением)
    void delete_element(int index); // Удаление элемента 

    void Clear();                   // Очистка массива

    std::string Print(int param=1); // Печать массива 
                                    // param=0 печатаем массив только фактическое количество
                                    // param=1 печатаем массив весь под который выделена память


    // Перегрузка оператора []
    int& operator[](int index);
    const int& operator[](int index) const;

    // Перегрузка оператора =    
    SmartArray& operator=(const SmartArray& other);
};

