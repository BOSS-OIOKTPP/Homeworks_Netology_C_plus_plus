#pragma once

#include <string>
#include <set>
#include "RaceParams.h"


class Transport
{
protected:
	std::set<RaceType> tRaces;  // Множество допустимых типов гонок	
	TransportType tType;    // Тип транспортного средства: наземный, воздушный
	TransportVid tVid;		// Вид транспортного средства
	int tV;					// Скорость транспортного средства
	int tDistance;          // Дистанция соревнования, заполняется функцией Calc()
	int tTime;              // Время прохождения дистанции, заполняется функцией Calc()

	int tRaceParticipant;    // tRaceParticipant=1 - участник гонки, иначе нет
public:
	Transport();
	virtual ~Transport() = default;   // Будем удалять объекты динамически, используя полиморфизм, т.е. ссылку на базовый класс, поэтому virtual. default - компилятор сам сформирует деструктор по умолчанию, а так же не требуется реализация
	TransportType Type();
	TransportVid Vid();
	int V();
	int Distance();
	int Time();
	void SetRaceParticipant(int P);
	bool canParticipate(RaceType RT);  // true - если может участвовать в гонке

	virtual void Calc(int distance) = 0;  // Функция отвечает за расчет времени, которое потребуется ТС на преодоление дистанции.
};

