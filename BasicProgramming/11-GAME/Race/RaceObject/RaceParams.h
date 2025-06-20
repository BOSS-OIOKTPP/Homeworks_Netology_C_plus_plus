#pragma once

#include <string>
#include "Transport.h"

#ifdef RACEOBJECT_EXPORTS
#define RACEOBJECT_API __declspec(dllexport)
#else
#define RACEOBJECT_API __declspec(dllimport)
#endif

enum class RaceType {
    ground = 1,         // Гонка для наземного транспорта
    air,                // Гонка для воздушного транспорта
    combined,           // Гонка для наземного и воздушного транспорта
    none                // нет данных
};
RACEOBJECT_API std::string GetRaceTypeName(RaceType R);

enum class TransportType {
    ground = 1,         // Наземный транспорт
    air,                // Воздушный транспорт
    none                // нет данных
};
RACEOBJECT_API std::string GetTransportTypeName(TransportType TT);

enum class TransportVid {
    boots = 1,          // Ботинки-вездеходы
    broom,              // Метла
    camel,              // Верблюд
    centaur,            // Кентавр
    eagle,              // Орел
    speed_camel,        // Верблюд-скороход
    flying_carpet,      // Ковер-самолет
    none                // нет данных
};
RACEOBJECT_API std::string GetTransportTypeName(TransportVid V);

struct TransportSelect {
    int boots = 0;          // Ботинки-вездеходы
    int broom = 0;          // Метла
    int camel = 0;          // Верблюд
    int centaur = 0;        // Кентавр
    int eagle = 0;          // Орел
    int speed_camel = 0;    // Верблюд-скороход
    int flying_carpet = 0;  // Ковер-самолет

    int GetCountSelect() { return boots + broom + camel + centaur + eagle + speed_camel + flying_carpet; }
};

// Параметры гонки
class Game {
private:
    RaceType race;                  // Выбранный тип гонки
    TransportSelect transport;      // Выбранные транспортные средства
    int distance;                   // Дистанция
public:
    // Проверка транспорта на соответствие гонке и проверка на 
    int CheckTransport(TransportVid TV, std::string& errName);

	//RACEOBJECT_API std::string leave(std::string name);
};
