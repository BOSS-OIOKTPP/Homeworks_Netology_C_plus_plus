// hw1-Addresses.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Задача 1. Адреса
// В этом задании вы будете читать адреса из файла и выводить их в другой файл в другом формате.
//
// Вам дан файл in.txt, в котором находится N адресов.Число N идёт первым в файле.
// После числа N располагаются N блоков по 4 строки в каждом.Каждый блок состоит из следующих строк : название города, название улицы, номер дома, номер квартиры.
//
// Задача программы заключается в том, чтобы считать адреса из файла in.txt и вывести их в файл out.txt в другом формате и в обратном порядке.
// Не забудьте вывести количество адресов в начале.
//
// Формат вывода адреса : <название города>, <название улицы>, <номер дома>, <номер квартиры>.
//
// Пример работы программы
// 
// in.txt
// 3
// Москва
// Строителей
// 34
// 12
// Омск
// Пушкина
// 2
// 13
// Новосибирск
// Мира
// 85
// 64
// 
// out.txt
// 3
// Новосибирск, Мира, 85, 64
// Омск, Пушкина, 2, 13
// Москва, Строителей, 34, 12

#include <iostream>
#include <fstream>
//#include <locale>
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

    std::string Get_City() {return FCity;}
    std::string Get_Street() { return FStreet; }
    int Get_House() { return FHouse; }
    int Get_Flat() { return FFlat; }

    void Set_City(std::string ACity) { FCity=ACity; }
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
    for (int i = 0;i < count;i++) {
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
        outFile << count << "\n";
        for (int i = count - 1;i >= 0; i--) {
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

