#include <cmath>
#include "SpeedCamel.h"

SpeedCamel::SpeedCamel() {
	tType = TransportType::ground;		// Наземный тип транспорта
	tVid = TransportVid::speed_camel;	// Верблюд
	tRaces.insert(RaceType::ground);	// Разрешаем участие в наземной гонке
	tRaces.insert(RaceType::combined);	// Разрешаем участие в комбинированной гонке
	tV = 40;							// Скорость транспортного средства
	DrivingTime = 10.0;					// Время движения до отдыха
	RestTime1 = 5.0;					// Длительность отдыха первый раз
	RestTime2 = 6.5;					// Длительность отдыха второй раз
	RestTime3 = 8.0;					// Длительность отдыха все последующие разы
}

// Рассчитываем время прохождения дистанции 
void SpeedCamel::Calc(int distance) {
	tDistance = distance;					// Запоминаем дистанцию	
	double t1 = std::round(tDistance / tV * 10) / 10;	// Время прохождения дистанции без отдыха. Время округляем до 1 знака после запятой
	int rest_count = t1 / DrivingTime;		// Количество остановок
	if (rest_count == 0) {
		tTime = t1;							// Время в пути без остановок
	}
	else if (rest_count == 1) {
		tTime = t1 + RestTime1;				// Время в пути с 1 остановкой
	}
	else if (rest_count == 2) {
		tTime = t1 + RestTime1 + RestTime2;	// Время в пути с 2-мя остановкой
	}
	else {									// Время в пути с более чем 2-мя остановками
		tTime = t1 + RestTime1 + RestTime2 + (rest_count - 2) * RestTime3;
	}
}

