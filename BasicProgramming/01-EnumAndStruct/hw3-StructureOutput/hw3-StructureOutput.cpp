// Задача 3. Вывод структуры
//
// Создайте структуру для хранения адреса.Структура должна содержать название города, улицы, номер дома, номер квартиры и индекс.
//
// Создайте функцию для вывода структуры на консоль.
//
// Протестируйте созданную функцию.Создайте в коде экземпляры структуры, передайте их в функцию и выведите на консоль получившиеся экземпляры структуры.
//
// Пример работы программы
// Город : Москва
// Улица : Арбат
// Номер дома : 12
// Номер квартиры : 8
// Индекс : 123456
//
// Город : Ижевск
// Улица : Пушкина
// Номер дома : 59
// Номер квартиры : 143
// Индекс : 953769


#include <iostream>
#include <locale>
#include <string>

struct address
{
    std::string city;      // город
    std::string street;    // улица
    int houseNumber;       // номер дома    
    int apartmentNumber;   // номер квартиры    
    int index;             // индекс
};

void print_address(address* pp);

int main()
{
    setlocale(LC_ALL, "russian");
    
    address p1;

    std::cout << "Введите адрес 1" << std::endl;
    std::cout << "Город : ";
    std::cin >> p1.city;

    std::cout << "Улица : ";
    std::cin >> p1.street;

    std::cout << "Номер дома : ";
    std::cin >> p1.houseNumber;
    // Очищаем буфер до символа новой строки, т.к. если ввести например так   1d , 
    // то программа прочитает 1, а потом вместо d вернет 0 и завершится.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Номер квартиры : ";
    std::cin >> p1.apartmentNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Индекс : ";
    std::cin >> p1.index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << std::endl;


    address p2;

    std::cout << "Введите адрес 2" << std::endl;
    std::cout << "Город : ";
    std::cin >> p2.city;

    std::cout << "Улица : ";
    std::cin >> p2.street;

    std::cout << "Номер дома : ";
    std::cin >> p2.houseNumber;
    // Очищаем буфер до символа новой строки, т.к. если ввести например так   1d , 
    // то программа прочитает 1, а потом вместо d вернет 0 и завершится.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Номер квартиры : ";
    std::cin >> p2.apartmentNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Индекс : ";
    std::cin >> p2.index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << std::endl;

    // Выводим на печать
    std::cout << "Выводим на печать адрес 1" << std::endl;
    print_address(&p1);
    std::cout << std::endl;
    std::cout << "Выводим на печать адрес 2" << std::endl;
    print_address(&p2);

    return 0;
}

void print_address(address* pp) {
    std::cout << "Город : " << pp->city << std::endl;
    std::cout << "Улица : " << pp->street << std::endl;
    std::cout << "Номер дома : " << pp->houseNumber << std::endl;
    std::cout << "Номер квартиры : " << pp->apartmentNumber << std::endl;
    std::cout << "Индекс : " << pp->index << std::endl;    
}


