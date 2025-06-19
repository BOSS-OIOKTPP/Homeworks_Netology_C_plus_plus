#pragma once

#include <string>

#ifdef RACEOBJECT_EXPORTS
#define RACEOBJECT_API __declspec(dllexport)
#else
#define RACEOBJECT_API __declspec(dllimport)
#endif

enum class RaceType {
    ground = 1,        // Гонка для наземного транспорта
    air,               // Гонка для воздушного транспорта
    combined,          // Гонка для наземного и воздушного транспорта
    none               // Гонка не выбрана
};

RACEOBJECT_API std::string GetRaceTypeName(RaceType R);

enum class TransportType {
    boots = 1,          // Ботинки-вездеходы
    broom,              // Метла
    camel,              // Верблюд
    centaur,            // Кентавр
    eagle,              // Орел
    speed_camel,        // Верблюд-скороход
    flying_carpet,      // Ковер-самолет
    none                // Транспорт не выбран
};

RACEOBJECT_API std::string GetTransportTypeName(TransportType T);

// Параметры гонки
class Params {
private:
    RaceType race;            // Тип гонки
    TransportType transport;  // Тип транспорта, участвующего в гонке
    int distance;             // Дистанция
public:


	//RACEOBJECT_API std::string leave(std::string name);
};
