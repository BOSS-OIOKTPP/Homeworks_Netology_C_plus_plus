#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>
#include "RaceParams.h"

// ***   Выбор гонки   ***
int RaceSelection(Game& game) {
    int intRace;
    while (true) {
        // Очищаем консоль от прошлой игры
        system("cls");

        std::cout << "Добро пожаловать в гоночный симулятор!" << std::endl;
        std::cout << "1. " << GetRaceTypeName(RaceType::ground) << std::endl;
        std::cout << "2. " << GetRaceTypeName(RaceType::air) << std::endl;
        std::cout << "3. " << GetRaceTypeName(RaceType::combined) << std::endl;
        std::cout << "Выберите тип гонки: ";

        std::cin >> intRace;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (intRace >= 1 && intRace <= 3) {
            game.SetRace(static_cast<RaceType>(intRace));
            break;
        }
    }
    return 0;
}

// ***   Выбор дистанции   ***
int DistanceSelection(Game& game) {
    int intRaceDistance;
    while (true) {
        std::cout << "Укажите длину дистанции (должна быть положительна, но не больше 100 000) : ";

        std::cin >> intRaceDistance;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (intRaceDistance > 0 && intRaceDistance <= 100000) {
            game.SetRaceDistance(intRaceDistance);
            break;
        }
        else {
            // Очищаем консоль
            system("cls");
            // Выводим статус игры
            game.PrintState();
        }
    }
    return 0;
}

// ***   Регистрация транспорта   ***
int TransportSelection(Game& game) {
    int intTransport;
    std::string strErr1;
    std::string strErr2;
    while (true) {
        // Очищаем консоль 
        system("cls");
        // Выводим статус игры
        game.PrintState();
        // Выводим список доступных для регистрации транспортных средств
        std::cout << "1. " << GetTransportVidName(TransportVid::boots) +
            ((game.IsTransportValidForRegistration(TransportVid::boots, strErr1) == false) ? "  +" : "") << std::endl;
        std::cout << "2. " << GetTransportVidName(TransportVid::broom) +
            ((game.IsTransportValidForRegistration(TransportVid::broom, strErr1) == false) ? "  +" : "") << std::endl;
        std::cout << "3. " << GetTransportVidName(TransportVid::camel) +
            ((game.IsTransportValidForRegistration(TransportVid::camel, strErr1) == false) ? "  +" : "") << std::endl;
        std::cout << "4. " << GetTransportVidName(TransportVid::centaur) +
            ((game.IsTransportValidForRegistration(TransportVid::centaur, strErr1) == false) ? "  +" : "") << std::endl;
        std::cout << "5. " << GetTransportVidName(TransportVid::eagle) +
            ((game.IsTransportValidForRegistration(TransportVid::eagle, strErr1) == false) ? "  +" : "") << std::endl;
        std::cout << "6. " << GetTransportVidName(TransportVid::speed_camel) +
            ((game.IsTransportValidForRegistration(TransportVid::speed_camel, strErr1) == false) ? "  +" : "") << std::endl;
        std::cout << "7. " << GetTransportVidName(TransportVid::flying_carpet) +
            ((game.IsTransportValidForRegistration(TransportVid::flying_carpet, strErr1) == false) ? "  +" : "") << std::endl;
        std::cout << "8. Закончить регистрацию" << std::endl;
        if (strErr2 != "")
            std::cout << strErr2 << std::endl;
        std::cout << "Выберите транспорт или 0 для окончания процесса регистрации: ";

        std::cin >> intTransport;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        // Если количество зарегистрированных ТС меньше 2, то возвращаемся в меню
        if (intTransport == 8 && game.GetTransportCount() >= 2) {
            std::cout << "Должно быть зарегистрировано хотябы 2 транспортных средства" << std::endl;
            break;
        }
        else if (intTransport == 8 && game.GetTransportCount() < 2) {
            strErr2 = "Должно быть зарегистрировано хотябы 2 транспортных средства";
        }
        // Регистрируем транспортное средство
        else if (intTransport >= 1 && intTransport <= 7) {
            Transport* T = game.CreateTransport(static_cast<TransportVid>(intTransport));
            // Проверяем, есть ли ошибки:
            // 1) соответствует типу гонки; 2) не зарегистрировано. 
            // true - есть ошибки.
            bool E = !game.IsTransportValidForRaceType(T, strErr2) || !game.IsTransportValidForRegistration(T, strErr2);
            if (!E) {
                game.AddTransport(T);
            }
        }
    }
    return 0;
}

// ***   Начать гонку   ***
int GameRun(Game& game) {
    int intRun;
    while (true) {
        // Очищаем консоль 
        system("cls");
        // Выводим статус игры
        game.PrintState();
        // Выводим меню
        std::cout << "1. Зарегистрировать транспорт" << std::endl;
        std::cout << "2. Начать гонку" << std::endl;        
        std::cout << "Выберите действие: ";

        std::cin >> intRun;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (intRun >= 1 && intRun <= 2) {
            // Запускаем гонку 
            if (intRun == 2) { game.Run(); }
            break;
        }
    }
    return intRun;
}

// *** Итоговое меню   ***
int MenuFinal(Game& game) {
    int intReplay;
    while (true) {        
        // Очищаем консоль 
        system("cls");
        // Выводим результаты
        game.PrintResult();

        // Выводим меню
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "1. Провести еще одну гонку" << std::endl;
        std::cout << "2. Выйти" << std::endl;
        std::cout << "Выберите действие: ";

        std::cin >> intReplay;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (intReplay >= 1 && intReplay <= 2) {
            break;
        }
    }
    return intReplay;
}



// ГЛАВНАЯ ПРОГРАММА
int main()
{    
    // Установка кодировки консоли Windows
    SetConsoleCP(65001);   // 1251
    SetConsoleOutputCP(65001);

    // Создали класс параметров игры и временные переменные
    Game game;
    int intRun;
    int intReplay;
    
    while (true) {
        // Инициируем объект
        game.InitGame();                
        intRun = 0;
        intReplay = 0;       

        // ***   Выбор гонки   ***
        RaceSelection(game);
        
        // ***   Выбор дистанции   ***
        DistanceSelection(game);
        
        while (true) {
            // ***   Регистрация транспорта   ***
            TransportSelection(game);

            // ***   Начать гонку   ***
            intRun = GameRun(game);
            if (intRun == 2) break;     // Был запуск игры, поэтому переходим к показу результатов
        }

        // *** Итоговое меню   ***
        intReplay = MenuFinal(game);        
        if (intReplay == 2) break;      // Выходим из игры        
    }

    std::cout << std::endl;
    std::cout << "Игра завершена! Нажмите любую клавишу." << std::endl;
    std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

