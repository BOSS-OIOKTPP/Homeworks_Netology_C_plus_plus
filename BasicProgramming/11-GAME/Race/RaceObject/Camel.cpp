#include <cmath>
#include "Camel.h"

// Верблюд
Camel::Camel() {
	tType = TransportType::ground;		// Наземный тип транспорта
	tVid = TransportVid::camel;			// Верблюд
	tRaces.insert(RaceType::ground);	// Разрешаем участие в наземной гонке
	tRaces.insert(RaceType::combined);	// Разрешаем участие в комбинированной гонке
	tV = 10;							// Скорость транспортного средства
	DrivingTime = 30.0;					// Время движения до отдыха
	RestTime1 = 5.0;					// Длительность отдыха первый раз
	RestTime2 = 8.0;					// Длительность отдыха все последующие разы
}

// Рассчитываем время прохождения дистанции 
void Camel::Calc(int distance) {
	tDistance = distance;				// Запоминаем дистанцию	
	double t1 = std::round(tDistance / tV * 10) / 10;	// Время прохождения дистанции без отдыха. Время округляем до 1 знака после запятой
	int rest_count = t1 / DrivingTime;	// Количество остановок
	if (rest_count == 0) {
		tTime = t1;						// Время в пути без остановок
	}
	else if (rest_count == 1) {
		tTime = t1 + RestTime1;			// Время в пути с 1 остановкой
	}
	else {								// Время в пути с более чем 1 остановкой
		tTime = t1 + RestTime1 + (rest_count - 1) * RestTime2;
	}
}
