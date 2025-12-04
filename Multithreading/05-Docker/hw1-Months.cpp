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
#include <limits>  // Добавили для numeric_limits

// Используем английские имена для enum (стандартная практика)
enum class months {
    january = 1,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
};

int main()
{
    setlocale(LC_ALL, "russian");  // Для вывода кириллицы в консоль

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
            return EXIT_SUCCESS;
        }

        m = static_cast<months>(n);

        // Выводим русские названия месяцев
        switch (m) {
        case months::january:  std::cout << "январь" << std::endl;  break;
        case months::february: std::cout << "февраль" << std::endl; break;
        case months::march:    std::cout << "март" << std::endl;    break;
        case months::april:    std::cout << "апрель" << std::endl;  break;
        case months::may:      std::cout << "май" << std::endl;     break;
        case months::june:     std::cout << "июнь" << std::endl;    break;
        case months::july:     std::cout << "июль" << std::endl;    break;
        case months::august:   std::cout << "август" << std::endl;  break;
        case months::september:std::cout << "сентябрь" << std::endl;break;
        case months::october:  std::cout << "октябрь" << std::endl; break;
        case months::november: std::cout << "ноябрь" << std::endl;  break;
        case months::december: std::cout << "декабрь" << std::endl; break;
        default:               std::cout << "неправильный номер!" << std::endl; break;
        }
    }
    return EXIT_SUCCESS;
}