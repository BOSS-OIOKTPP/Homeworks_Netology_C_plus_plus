#include "Сentaur.h"

// Кентавр
Centaur::Centaur() {
	tType = TransportType::ground;		// Наземный тип транспорта
	tVid = TransportVid::centaur;		// Кентавр
	tV = 15;							// Скорость транспортного средства
	DrivingTime = 8;					// Время движения до отдыха
	RestTime = 2;						// Длительность отдыха	
}

// Рассчитываем время прохождения дистанции 
void Centaur::Calc(int distance) {
	tDistance = distance;				// Запоминаем дистанцию
	int t1 = tDistance / tV;			// Время прохождения дистанции без отдыха
	int rest_count = t1 / DrivingTime;	// Количество остановок
	if (rest_count == 0) {
		tTime = t1;						// Время в пути без остановок
	}	
	else {								// Время в пути с остановками
		tTime = t1 + rest_count * RestTime;
	}
}

