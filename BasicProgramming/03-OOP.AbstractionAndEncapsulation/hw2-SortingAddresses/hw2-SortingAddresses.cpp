// hw2-SortingAddresses.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

// Задача 2. Сортируем адреса
// В этом задании вы будете читать из файла адреса и выводить их в другой файл в другом формате, отсортированными по названию города.
//
// Вам дан файл in.txt, в котором находится N адресов.Число N идёт первым в файле.После числа N располагаются N блоков по 4 строки в каждом.
// Каждый блок состоит из следующих строк : название города, название улицы, номер дома, номер квартиры.
//
// Задача программы заключается в том, чтобы считать адреса из файла in.txt, отсортировать их по названию города и вывести отсортированный список адресов в файл out.txt в другом формате.Не забудьте вывести количество адресов в начале.
//
// Города должны быть отсортированы в алфавитном порядке.
//
// Формат вывода адреса : <название города>, <название улицы>, <номер дома>, <номер квартиры>.
//
// Пример работы программы
// in.txt
// 5
// Москва
// Строителей
// 34
// 12
// Новокузнецк
// Науки
// 5
// 16
// Омск
// Пушкина
// 2
// 13
// Москва
// Арбат
// 4
// 1
// Новосибирск
// Мира
// 85
// 64
// 
// out.txt
// 5
// Москва, Строителей, 34, 12
// Москва, Арбат, 4, 1
// Новокузнецк, Науки, 5, 16
// Новосибирск, Мира, 85, 64
// Омск, Пушкина, 2, 13



#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

class TAddress {
private:
    std::string FCity;    // Город
    std::string FStreet;  // Улица
    int FHouse;           // Дом
    int FFlat;            // Квартира
public:
    // Конструктор
    TAddress(std::string ACity, std::string AStreet, int AHouse, int AFlat) {
        FCity = ACity;
        FStreet = AStreet;
        FHouse = AHouse;
        FFlat = AFlat;
    };

    std::string Get_City() { return FCity; }
    std::string Get_Street() { return FStreet; }
    int Get_House() { return FHouse; }
    int Get_Flat() { return FFlat; }

    void Set_City(std::string ACity) { FCity = ACity; }
    void Set_Street(std::string AStreet) { FStreet = AStreet; }
    void Set_House(int AHouse) { FHouse = AHouse; }
    void Set_Flat(int AFlat) { FFlat = AFlat; }

    // Полный адрес
    std::string Get_Address() { return FCity + ", " + FStreet + ", " + std::to_string(FHouse) + ", " + std::to_string(FFlat); }

};

int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // подключаем файл
    std::ifstream inFile("in.txt");
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл для чтения!" << std::endl;
        inFile.close();
        return 1;
    }

    // читаем размерность массива
    int count{};
    inFile >> count;

    // Создаем массив указателей
    TAddress** arrPObjects = new TAddress * [count];

    // Заполняем массив
    for (int i = 0; i < count; i++) {
        std::string city, street;
        int house, flat;

        std::getline(inFile >> std::ws, city);
        std::getline(inFile >> std::ws, street);
        inFile >> house;
        inFile >> flat;

        // Создаем объект и запоминаем ссылку на него в массиве
        arrPObjects[i] = new TAddress(city, street, house, flat);
    }

    // Сохраняем в файл результат
    std::ofstream outFile("out.txt");
    if (!outFile.is_open()) {
        std::cout << "Не удалось создать файл для записи!" << std::endl;
    }
    else {
        // Сортировка по полю City
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (arrPObjects[j]->Get_City() > arrPObjects[j + 1]->Get_City()) {
                    // Меняем местами указатели
                    TAddress* temp = arrPObjects[j];
                    arrPObjects[j] = arrPObjects[j + 1];
                    arrPObjects[j + 1] = temp;
                }
            }
        }

        outFile << count << "\n";
        for (int i = 0; i < count; i++) {
            outFile << arrPObjects[i]->Get_Address() << "\n";
        }

        std::cout << "Файл 'out.txt' записан!" << std::endl;
    }

    // очищаем память   
    for (int i = 0; i < count; ++i) {
        delete arrPObjects[i];  // Удаляем каждый объект
    }
    delete[] arrPObjects;      // Удаляем массив указателей

    inFile.close();
    outFile.close();

    return 0;
}

