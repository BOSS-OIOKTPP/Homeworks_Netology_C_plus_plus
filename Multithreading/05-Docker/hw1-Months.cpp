// Задача 1. Месяцы
// 
// Напишите программу, которая спрашивает у пользователя номер месяца и выводит на экран название месяца, введённого пользователем.
// Если пользователь ввёл некорректный номер месяца, сообщите ему об этом.
// Спрашивайте пользователя до тех пор, пока он не введёт 0.
// Для решения задачи воспользуйтесь перечислением.

// Пример работы программы
// введите номер месяца : 1
// январь
// введите номер месяца : 7
// июль
// введите номер месяца : 13
// неправильный номер!
// введите номер месяца : 0
// до свидания
//

#include <iostream>
#include <locale>

enum class months { 
    январь=1,
    февраль,
    март,
    апрель,
    май,
    июнь,
    июль,
    август,
    сентябрь,
    октябрь,
    ноябрь,
    декабрь
};


int main()
{
    setlocale(LC_ALL, "russian");

    int n{ -1 }; // Номер месяца
    months m{};  // месяц
   
    while (true) {
        n = -1;
               
        std::cout << "Введите номер месяца : ";
        std::cin >> n;
 
        // Очищаем буфер до символа новой строки, т.к. если ввести например так   1d , 
        // то программа прочитает 1, а потом вместо d вернет 0 и завершится.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        
        if (n == 0) {
            std::cout << "до свидания" << std::endl;
            return 0;
        }

        m = static_cast<months>(n);        

        switch (m) {
        case months::январь:
            std::cout << "январь" << std::endl;
            break;
        case months::февраль:
            std::cout << "февраль" << std::endl;
            break;
        case months::март:
            std::cout << "март" << std::endl;
            break;
        case months::апрель:
            std::cout << "апрель" << std::endl;
            break;
        case months::май:
            std::cout << "май" << std::endl;
            break;
        case months::июнь:
            std::cout << "июнь" << std::endl;
            break;
        case months::июль:
            std::cout << "июль" << std::endl;
            break;
        case months::август:
            std::cout << "август" << std::endl;
            break;
        case months::сентябрь:
            std::cout << "сентябрь" << std::endl;
            break;
        case months::октябрь:
            std::cout << "октябрь" << std::endl;
            break;
        case months::ноябрь:
            std::cout << "ноябрь" << std::endl;
            break;
        case months::декабрь:
            std::cout << "декабрь" << std::endl;
            break;
        default:
            std::cout << "неправильный номер!" << std::endl;            
            break;
        }
    }
    return 0;
}