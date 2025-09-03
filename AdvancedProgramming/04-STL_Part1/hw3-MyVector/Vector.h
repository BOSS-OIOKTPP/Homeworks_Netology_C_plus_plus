#pragma once
#include <initializer_list>
#include <stdexcept>
#include <string>

template<typename T>
class Vector {
private:
    T* FData;             // Указатель на массив
    int FCapacity;        // Количество элементов под которое выделена память
    int FSize;            // Фактическое количество элементов   
public:
    // Конструктор по умолчанию
    Vector():FData(nullptr), FCapacity(10), FSize(0) { FData = new T[FCapacity]; }
    // Конструктор
    Vector(int capacity) : FData(new T[capacity]), FCapacity(capacity), FSize(0) {}
    // Конструктор со списковой инициализацией
    Vector(std::initializer_list<T> initList): FCapacity(initList.size() * 2), FSize(initList.size()) {
        FData = new T[FCapacity];
        int i = 0;
        for (const auto& item : initList) 
            FData[i++] = item;        
    }

    // Деструктор
    ~Vector() {
        delete[] FData;
    };

    // Количество элементов под которое выделена память
    int Capacity() const { return FCapacity; };
    // Фактическое количество элементов   
    int Size() const { return FSize; };

    // Добавление элемента с динамическим расширением
    void Push_Back(T value) {
        // Создаем массив в 2 раза больше чем был и 
        // копируем в него данные из первово массива
        if (FSize == FCapacity) {
            // Запоминаем новое значение размера выделенной памяти для массива
            FCapacity *= 2;
            T* newData = new T[FCapacity];
            for (int i = 0; i < FSize; ++i)
                newData[i] = FData[i];
            // Удаляем старый массив
            delete[] FData;
            // Запоминаем ссылку на новый массив
            FData = newData;
        }

        // Запоминаем введенное значение и
        // увеличиваем фактическое количество на 1
        FData[FSize++] = value;
    }

    // доступ к элементу контейнера по индексу;
    T& At(int index) { 
        // Проверка корректности индекса
        if (index < 0 || index >= FSize) {
            throw std::out_of_range(
                "Индекс " + std::to_string(index) +
                " выходит за границу массива, допустимое значение [0; " +
                std::to_string(FSize - 1) + "]");
        }
        return FData[index]; 
    }
    
    // Печать массива
    std::string Print_Vector() {
        std::string str;
        str = "";
        // фактическое количество
        for (int i = 0; i < FSize; ++i)
            str += std::to_string(FData[i]) + " ";        
        return str;
    }


    // Удаление элемента 
    void Erase(int index) {
        // Проверка корректности индекса
        if (index < 0 || index >= FSize) {
            throw std::out_of_range(
                "Индекс " + std::to_string(index) +
                " выходит за границу массива, допустимое значение [0; " +
                std::to_string(FSize - 1) + "]");
        }
        // Сдвигаем все элементы после удаляемого на одну позицию влево
        for (int i = index; i < FSize - 1; ++i)
            FData[i] = FData[i + 1];
        // Уменьшаем на 1 фактическое количество элементов
        FSize--;

        // Уменьшаем размер массива если он слишком пустой
        if (FSize > 0 && FSize < FCapacity / 4) {
            FCapacity /= 2;
            T* newData = new T[FCapacity];
            for (int i = 0; i < FSize; ++i)
                newData[i] = FData[i];
            delete[] FData;
            FData = newData;
        }
    }

    // Очистка массива с полным освобождением памяти
    void Clear() {
        delete[] FData;
        FSize = 0;
        FCapacity = 10;
        FData = new T[FCapacity];
    }

    // Перегрузка оператора [] 
    T& operator[](int index) {
        if (index >= FSize) {
            throw std::out_of_range(
                "Индекс " + std::to_string(index) +
                " выходит за границу массива, допустимое значение [0; " +
                std::to_string(FSize - 1) + "]");
        }
        return FData[index];
    }
    const T& operator[](int index) const {
        return operator[](index); // Вызываем неконстантную версию
    }

    // Перегрузка оператора = 
    Vector& operator=(const Vector& other) {
        if (this != &other) { // Проверка на самоприсваивание
            // Освобождаем текущие ресурсы
            delete[] FData;
            // Копируем данные из другого объекта
            FCapacity = other.FCapacity;
            FSize = other.FSize;
            FData = new T[FCapacity];

            // Копируем элементы массива
            for (int i = 0; i < FSize; ++i) 
                FData[i] = other.FData[i];            
        }
        return *this;
    }
};

