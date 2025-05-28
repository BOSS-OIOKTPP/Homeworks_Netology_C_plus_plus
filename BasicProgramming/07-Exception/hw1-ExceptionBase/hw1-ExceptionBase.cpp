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
    const char* what() const override { return "Вы ввели слово запретной длины! "; }
};

int fnLen(std::string str, int forbidden_length) {    
    if (str.length() == forbidden_length) { throw bad_length(); }    
    return str.length();
}

int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int LenErr{};   // Запретная длина
    std::string Word;    

    std::cout << "Введите запретную длину: ";
    std::cin >> LenErr;
    std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

    while (true) {
        std::cout << "Введите слово: ";
        std::getline(std::cin, Word);
        try
        {
            std::cout << "Длина слова \"" << Word <<"\" равна " << fnLen(Word, LenErr) << std::endl;
        }
        catch (const bad_length& ex) { 
            std::cout << ex.what() << "До свидания!" << std::endl;            
            return 1;  
        }
    } 

    return 0;
}
