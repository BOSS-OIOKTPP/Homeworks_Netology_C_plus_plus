#include <cmath>
#include "Boots.h"
#include "RaceParams.h"

Boots::Boots() {
	tType = TransportType::ground;		// Наземный тип транспорта
	tVid = TransportVid::boots;			// Ботинки-вездеходы
	tRaces.insert(RaceType::ground);	// Разрешаем участие в наземной гонке
	tRaces.insert(RaceType::combined);	// Разрешаем участие в комбинированной гонке
	tV = 6;								// Скорость транспортного средства
	DrivingTime = 60,0;					// Время движения до отдыха
	RestTime1 = 10.0;					// Длительность отдыха первый раз
	RestTime2 = 5.0;					// Длительность отдыха все последующие разы
}

// Рассчитываем время прохождения дистанции ботинками
void Boots::Calc(int distance) {
	tDistance = distance;						// Запоминаем дистанцию
	double t1 = std::round(tDistance/tV*10)/10;	// Время прохождения дистанции без отдыха. Время округляем до 1 знака после запятой
	int rest_count = t1 / DrivingTime;			// Количество остановок
	if (rest_count==0) {
		tTime = t1;								// Время в пути без остановок
	}
	else if (rest_count == 1) {
		tTime = t1+ RestTime1;					// Время в пути с 1 остановкой
	}
	else {										// Время в пути с более чем 1 остановкой
		tTime = t1 + RestTime1 + (rest_count-1)* RestTime2;
	}
}