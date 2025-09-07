#pragma once
#include <string>

template<typename T>
class Array {
private:    
    T* FData;         // Указатель на массив
    int FSize;        // Количество элементов
public: 
    // Конструктор по умолчанию
    Array() : FData(nullptr), FSize(0) {}

    // Конструктор
    Array(int size) : FData(new T[size]), FSize(size) {}

    // Конструктор копирования
    Array(const Array& other) : FData(nullptr), FSize(0) {
        *this = other; // Используем уже реализованный operator=
    }

    // Деструктор
    ~Array() {
        delete[] FData;
    }
    
    // Количество элементов
    int Size() const {
        return FSize;
    }
    // Перегрузка оператора []
    T& operator[](int index) {
        if (index >= FSize) {
            //throw std::out_of_range("Index out of range");
            throw std::out_of_range(
                "Индекс массива " + std::to_string(index) + 
                " выходит за границу [0; " + std::to_string(FSize - 1) + "]"
            );
        }
        return FData[index];
    }
    // Перегрузка const оператора []
    const T& operator[](int index) const {
        return operator[](index); // Вызываем неконстантную версию
    }

    // Перегрузка оператора =    
    Array& operator=(const Array& other) {
        if (this != &other) { // Проверка на самоприсваивание
            // Освобождаем текущие ресурсы
            delete[] FData;

            // Копируем данные из другого объекта
            FSize = other.FSize;
            FData = new T[FSize];

            // Копируем элементы массива
            for (int i = 0; i < FSize; ++i) {
                FData[i] = other.FData[i];
            }
        }
        return *this;
    }

    // Печать массива
    std::string Print() {
        std::string str{""};        
        for (int i = 0; i < FSize; ++i)
            str += std::to_string(FData[i]) + " ";        
        return str;
    }

};

