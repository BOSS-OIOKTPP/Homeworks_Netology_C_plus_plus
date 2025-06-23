#pragma once

#include <string>
#include "Transport.h"
#include <vector>

// Параметры гонки
class Game {
private:
    RaceType Race;                      // Выбранный тип гонки
    std::vector<Transport*> Transports; // Массив указателей на транспортные средства участвующие в гонке        
    int RaceDistance;                   // Дистанция
public:
    ~Game();

    // Очищаем список транспортных средств
    void Clear();
    // Добавляем транспорт для гонок нужного типа
    void AddTransport(Transport* T);

    // Проверка транспорта на соответствие гонке
    // true - транспорт соответствует выбранной гонке
    bool IsTransportValidForRaceType(Transport& T, std::string& E);

    // Проверка транспорта на регистрацию, зарегистрировать транспорт можно только 1 раз
    // true - транспорт еще не зарегистрирован на гонку
    bool IsTransportValidForRegistration(Transport& T, std::string& E);

    

	//RACEOBJECT_API std::string leave(std::string name);
};
