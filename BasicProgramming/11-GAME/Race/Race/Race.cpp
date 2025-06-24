#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>
#include "RaceParams.h"


int main()
{    
    // Установка кодировки консоли Windows
    SetConsoleCP(65001);   // 1251
    SetConsoleOutputCP(65001);

    // Создали класс параметров игры и временные переменные
    Game game;
    int intRace;
    int intRaceDistance;
    int intTransport;
    int intRun;
    int intReplay;

    while (true) {
        // Инициируем объект
        game.InitGame();
        // Очищаем переменные
        intRace = 0;
        intRaceDistance = 0;
        intTransport = 0;
        intRun = 0;
        intReplay = 0;

        // Меню
        // ***   Выбор гонки   ***
        while (true) {
            // Очищаем консоль от прошлой игры
            system("cls");

            std::cout << "Добро пожаловать в гоночный симулятор!" << std::endl;
            std::cout << "1. " << GetRaceTypeName(RaceType::ground) << std::endl;
            std::cout << "2. " << GetRaceTypeName(RaceType::air)  << std::endl;
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
        // ***   Выбор дистанции   ***
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
        // ***   Регистрация транспорта   ***
        while (true) {
            // Очищаем консоль 
            system("cls");
            // Выводим статус игры
            game.PrintState();
            // Выводим список доступных для регистрации транспортных средств
            std::cout << "1. " << GetTransportVidName(TransportVid::boots) + 
                                ((game.IsTransportValidForRegistration(TransportVid::boots) == false) ? "  +" : "") << std::endl;
            std::cout << "2. " << GetTransportVidName(TransportVid::broom) + 
                                ((game.IsTransportValidForRegistration(TransportVid::broom) == false) ? "  +" : "") << std::endl;
            std::cout << "3. " << GetTransportVidName(TransportVid::camel) + 
                                ((game.IsTransportValidForRegistration(TransportVid::camel) == false) ? "  +" : "") << std::endl;
            std::cout << "4. " << GetTransportVidName(TransportVid::centaur) + 
                                ((game.IsTransportValidForRegistration(TransportVid::centaur) == false) ? "  +" : "") << std::endl;
            std::cout << "5. " << GetTransportVidName(TransportVid::eagle) + 
                                ((game.IsTransportValidForRegistration(TransportVid::eagle) == false) ? "  +" : "") << std::endl;
            std::cout << "6. " << GetTransportVidName(TransportVid::speed_camel) + 
                                ((game.IsTransportValidForRegistration(TransportVid::speed_camel) == false) ? "  +" : "") << std::endl;
            std::cout << "7. " << GetTransportVidName(TransportVid::flying_carpet) + 
                                ((game.IsTransportValidForRegistration(TransportVid::flying_carpet) == false) ? "  +" : "") << std::endl;
            std::cout << "0. Закончить регистрацию" << std::endl;
            std::cout << "Должно быть зарегистрировано хотябы 2 транспортных средства" << std::endl;
            std::cout << "Выберите транспорт или 0 для окончания процесса регистрации: " << std::endl;

            std::cin >> intTransport;
            std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

            // Если количество зарегистрированных ТС меньше 2, то возвращаемся в меню
            if (intTransport == 0 && game.GetTransportCount()>=2) {
                break;
            } 
            // Регистрируем транспортное средство
            else if (intTransport >= 1 && intTransport <= 7) {
                // Если не зарегистрировано, то регистрируем
                if ( game.IsTransportValidForRegistration(static_cast<TransportVid>(intTransport)) ) {
                    game.AddTransport(game.CreateTransport(static_cast<TransportVid>(intTransport)));
                }
            }
        }
        // ***   Начать гонку   ***
        while (true) {
            // Очищаем консоль 
            system("cls");
            // Выводим статус игры
            game.PrintState();
            // Выводим меню
            std::cout << "1. Начать гонку" << std::endl;
            std::cout << "2. Повторить ввод параметров" << std::endl;
            std::cout << "3. Выйти" << std::endl;
            std::cout << "Выберите действие: " << std::endl;

            std::cin >> intRun;
            std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
            
            if (intRun >= 1 && intRun <= 3) {
                if (intRun == 1) {
                    // Запускаем гонку
                    game.Run();
                }
                break;
            }            
        }

        // Запускаем игру по новой
        if (intRun == 2) continue;
        // Выходим из игры
        if (intRun == 3) break;

        // *** Итоговое меню 
        while (true) {
            if (intRun == 1) {
                // Очищаем консоль 
                system("cls");
                // Выводим результаты
                game.PrintResult();
            }

            // Выводим меню
            std::cout << "1. Провести еще одну гонку" << std::endl;            
            std::cout << "2. Выйти" << std::endl;
            std::cout << "Выберите действие: " << std::endl;

            std::cin >> intReplay;
            std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

            if (intRun >= 1 && intRun <= 2) {
                break;
            }
        }
        // Запускаем игру по новой
        if (intReplay == 1) continue;
        // Выходим из игры
        if (intReplay == 2) break;
    }

    std::cout << "Игра завершена! Нажмите любую клавишу." << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

