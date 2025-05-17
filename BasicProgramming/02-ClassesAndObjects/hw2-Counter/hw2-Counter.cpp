//Задача 2. Счётчик
//В этом задании вам нужно будет создать класс - счётчик
//
//Создайте класс Counter.Класс должен выполнять функцию счётчика, для этого он должен предоставлять :
//
//возможность увеличить своё значение на 1
//возможность уменьшить своё значение на 1
//возможность посмотреть своё текущее значение
//возможность создания экземпляра класса с начальным значением по умолчанию(1)
//возможность создания экземпляра класса с инициализирующим начальным значением
//Обратите внимание на то, что у внешнего кода не должно быть возможности изменить внутреннее значение счётчика напрямую
//
//Напишите код, демонстрирующий работу класса Counter.Спросите у пользователя, хочет ли он указать начальное значение для счётчика.Если хочет, дайте ему возможность это сделать.Затем предоставьте пользователю возможность вводить команды :
//
//+: увеличьте счётчик на 1
//- : уменьшите счётчик на 1
//= : выведите текущее значение счётчика
//x : завершите работу программы
//Пример работы программы
//Консоль
//Вы хотите указать начальное значение счётчика ? Введите да или нет : да
//Введите начальное значение счётчика : 6
//Введите команду('+', '-', '=' или 'x') : +
//Введите команду('+', '-', '=' или 'x') : +
//Введите команду('+', '-', '=' или 'x') : =
//8
//Введите команду('+', '-', '=' или 'x') : -
//Введите команду('+', '-', '=' или 'x') : =
//7
//Введите команду('+', '-', '=' или 'x') : x
//До свидания!



#include <iostream>
#include <locale>
#include <string>
#include <windows.h>

class Counter {
private:
    int num;

public:
    Counter(int num=1) {
        this->num = num;
    };

    void inc() {
        num++;
    };

    void dec() {
        num--;
    };

    int getNum() {
        return num;
    }
};

int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // setlocale(LC_ALL, "");

    //setlocale(LC_ALL, "ru_RU.UTF-8");
    //setlocale(LC_ALL, "russian");
    //if (setlocale(LC_ALL, "ru-RU") == NULL) {
    //    std::cout << "Error set locale ru-RU." << std::endl;
    //    return -1;
    //    // или принудительно ставим таблицу 1251 через SetConsoleCP.
    //    // выше пример есть. И не забываем проверять результат SetConsoleCP
    //    // Если ошибка возникла, то код ошибки смотрим через GetLastError.
    //}


    char chSymbol;
    int num{ 1 };
    std::string strSymbol;
    bool setValue{ true };

    do {
        std::cout << "Вы хотите указать начальное значение счётчика ? Введите да или нет : ";
        std::cin >> strSymbol;
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

//        std::cout << "." << strSymbol << std::endl;     // ТЕСТ - Показываем в консоле то, что прочитали

        if (strSymbol == "да") {
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

    return 0;
}
