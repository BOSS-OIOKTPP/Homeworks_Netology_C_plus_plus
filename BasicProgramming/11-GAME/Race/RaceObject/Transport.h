#pragma once

#include <string>
#include "RaceParams.h"


class Transport
{
protected:
	TransportType tType;    // Тип транспортного средства: наземный, воздушный
	TransportVid tVid;		// Вид транспортного средства
	int tV;					// Скорость транспортного средства
	int tDistance;          // Дистанция соревнования, заполняется функцией Calc()
	int tTime;              // Время прохождения дистанции, заполняется функцией Calc()
public:
	Transport();

	TransportType Type();
	TransportVid Vid();
	int V();
	int Distance();
	int Time();

	virtual void Calc(int distance);  // Функция отвечает за расчет времени, которое потребуется ТС на преодоление дистанции.
};

