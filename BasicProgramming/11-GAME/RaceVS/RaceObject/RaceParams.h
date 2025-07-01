#pragma once

#include <string>
#include <vector>
#include "Transport.h"

// Параметры гонки
class Game {
private:
    RaceType Race;                      // Выбранный тип гонки
    std::vector<Transport*> Transports; // Массив указателей на транспортные средства участвующие в гонке        
    int RaceDistance;                   // Дистанция
public:
    RACEOBJECT_API Game();

    RACEOBJECT_API ~Game();

    // Подготовка объекта к работе
    RACEOBJECT_API void InitGame();
    // Очищаем список транспортных средств
    RACEOBJECT_API void ClearGame();
    // Создаем транспорт 
    RACEOBJECT_API Transport* CreateTransport(TransportVid TV);
    // Добавляем транспорт для гонок нужного типа
    RACEOBJECT_API void AddTransport(Transport* T);
    // Определяем количество зарегистрированных транспортных средств
    RACEOBJECT_API size_t GetTransportCount();
    // Записываем тип гонки
    RACEOBJECT_API void SetRace(RaceType R);
    // Записываем дистанцию гонки
    RACEOBJECT_API void SetRaceDistance(int D);
    // Прочитали тип гонки
    RACEOBJECT_API RaceType GetRace();
    // Прочитали дистанцию гонки
    RACEOBJECT_API int GetRaceDistance();
     

    // Проверка транспорта на соответствие гонке
    // true - транспорт соответствует выбранной гонке
    RACEOBJECT_API bool IsTransportValidForRaceType(Transport* T, std::string& E);
    // Проверка транспорта на регистрацию, зарегистрировать транспорт можно только 1 раз
    // true - транспорт еще не зарегистрирован на гонку
    RACEOBJECT_API bool IsTransportValidForRegistration(Transport* T, std::string& E);
    RACEOBJECT_API bool IsTransportValidForRegistration(TransportVid TV, std::string& E);

    
    // Печать состояния игры
    RACEOBJECT_API void PrintState();

    // Печать результатов игры
    RACEOBJECT_API void PrintResult();

    // Запускаем гонку
    RACEOBJECT_API void Run();

    // Сортировка транспортных средств по времени прохождения дистанции. Самые быстрые на первом месте
    RACEOBJECT_API void Sort();
};
