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
