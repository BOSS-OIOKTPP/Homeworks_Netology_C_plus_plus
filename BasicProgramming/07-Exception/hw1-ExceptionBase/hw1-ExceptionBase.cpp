// hw1-ExceptionBase.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// 
//Задача 1. Простое исключение
//В этом задании вы попробуете выбросить и обработать исключение.
//
//Создайте функцию int function(std::string str, int forbidden_length).Эта функция должна возвращать длину переданной строки, если эта длина не равна значению переданного параметра forbidden_length.В противном случае она должна выбрасывать исключение bad_length.
//
//Для проверки функции организуйте работу с пользователем.В начале задайте запретную длину, а затем считывайте пользовательские строки и выводите их длину до тех пор, пока пользователь не введёт строку запретной длины.После этого сообщите ему, что он ввёл строку запретной длины, и завершите программу.
//
//Пример работы программы
//Консоль
//Введите запретную длину : 5
//Введите слово : Привет
//Длина слова "Привет" равна 6
//Введите слово : мир
//Длина слова "мир" равна 3
//Введите слово : пирог
//Вы ввели слово запретной длины!До свидания

#include <iostream>
#include <string>
#include <windows.h>

class bad_length : public std::exception
{
public:
    const char* what() const override { return "Вы ввели слово запретной длины!"; }
};

int fnLen(std::string str, int forbidden_length) {
    
    if (str.length() == forbidden_length) {
        throw bad_length();
    }
    
    return str.length();
}

int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int LenErr{};   // Запретная длина
    std::string Word;
    bool setValue{ true };

    std::cout << "Введите запретную длину: ";
    std::cin >> LenErr;
    std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

    do {
        std::cout << "Введите слово: ";
        std::cin >> Word;
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');        
        try
        {
            std::cout << "Длина слова """ << Word <<""" равна " << fnLen(Word, LenErr) << std::endl;
        }
        catch (const bad_length& ex) { 
            std::cout << ex.what() << "До свидания" << std::end;            
            return 1;  
        }


        if (std::string::length(Word) == LenErr) {
            std::cout << "Введите начальное значение счётчика : ";
            std::cin >> num;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
            // Записали значение пользователя
            setValue = true;
        }
        else if (strSymbol == "нет") {
            setValue = true;
        }
        else {
            std::cout << "Некорректный ввод!" << std::endl;
            setValue = false;
        }
    } while (setValue == false);

    Counter objCounter(num);

    setValue = false;
    do {
        std::cout << "Введите команду('+', '-', '=' или 'x') : ";
        std::cin >> chSymbol;
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
        if (chSymbol == '+') {
            objCounter.inc();
        }
        else if (chSymbol == '-') {
            objCounter.dec();
        }
        else if (chSymbol == '=') {
            std::cout << objCounter.getNum() << std::endl;
        }
        else if (chSymbol == 'x') {
            std::cout << "До свидания!" << std::endl;
            setValue = true;
        }
        else {
            std::cout << "Некорректный ввод!" << std::endl;
        }
    } while (setValue == false);


}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
