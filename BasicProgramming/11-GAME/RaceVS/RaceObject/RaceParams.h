#pragma once

#include <string>
#include <vector>
#include "Transport.h"

// Параметры гонки
class RACEOBJECT_API Game {
private:
    RaceType Race;                      // Выбранный тип гонки
    std::vector<Transport*> Transports; // Массив указателей на транспортные средства участвующие в гонке        
    int RaceDistance;                   // Дистанция
public:
    ~Game();

    // Подготовка объекта к работе
    void InitGame();
    // Очищаем список транспортных средств
    void ClearGame();
    // Создаем транспорт 
    Transport* CreateTransport(TransportVid TV);
    // Добавляем транспорт для гонок нужного типа
    void AddTransport(Transport* T);
    // Определяем количество зарегистрированных транспортных средств
    size_t GetTransportCount();
    // Записываем тип гонки
    void SetRace(RaceType R);
    // Записываем дистанцию гонки
    void SetRaceDistance(int D);
    // Прочитали тип гонки
    RaceType GetRace();
    // Прочитали дистанцию гонки
    int GetRaceDistance();
     

    // Проверка транспорта на соответствие гонке
    // true - транспорт соответствует выбранной гонке
    bool IsTransportValidForRaceType(Transport* T, std::string& E);
    // Проверка транспорта на регистрацию, зарегистрировать транспорт можно только 1 раз
    // true - транспорт еще не зарегистрирован на гонку
    bool IsTransportValidForRegistration(Transport* T, std::string& E);    
    bool IsTransportValidForRegistration(TransportVid TV, std::string& E);

    
    // Печать состояния игры
    void PrintState();

    // Печать результатов игры
    void PrintResult();

    // Запускаем гонку
    void Run();

    // Сортировка транспортных средств по времени прохождения дистанции. Самые быстрые на первом месте
    void Sort(); 
};
