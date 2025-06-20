#include "Camel.h"

Camel::Camel() {
	tType = TransportType::ground;	// Наземный тип транспорта
	tVid = TransportVid::camel;		// Верблюд
	tV = 10;						// Скорость транспортного средства
	DrivingTime = 30;				// Время движения до отдыха
	RestTime1 = 5;					// Длительность отдыха первый раз
	RestTime2 = 8;					// Длительность отдыха все последующие разы
}

// Рассчитываем время прохождения дистанции 
void Camel::Calc(int distance) {
	tDistance = distance;				// Запоминаем дистанцию
	int t1 = tDistance / tV;			// Время прохождения дистанции без отдыха
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
