#pragma once

#ifdef RACEOBJECT_EXPORTS
#define RACEOBJECT_API __declspec(dllexport)
#else
#define RACEOBJECT_API __declspec(dllimport)
#endif


#include <set>
#include <string>

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
RACEOBJECT_API std::string GetTransportVidName(TransportVid V);


class Transport
{
protected:
	std::set<RaceType> tRaces;  // Множество допустимых типов гонок	
	TransportType tType;		// Тип транспортного средства: наземный, воздушный
	TransportVid tVid;			// Вид транспортного средства
	int tV;						// Скорость транспортного средства
	int tDistance;				// Дистанция соревнования, заполняется функцией Calc()
	double tTime;				// Время прохождения дистанции, заполняется функцией Calc()
public:
	Transport();
	virtual ~Transport() = default;   // Будем удалять объекты динамически, используя полиморфизм, т.е. ссылку на базовый класс, поэтому virtual. default - компилятор сам сформирует деструктор по умолчанию, а так же не требуется реализация
	TransportType Type();
	TransportVid Vid();
	int V();
	int Distance();
	double Time();
	bool canParticipate(RaceType RT);  // true - если может участвовать в гонке

	virtual void Calc(int distance) = 0;  // Функция отвечает за расчет времени, которое потребуется ТС на преодоление дистанции.
};

