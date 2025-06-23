#include <cmath>
#include "Centaur.h"

// Кентавр
Centaur::Centaur() {
	tType = TransportType::ground;		// Наземный тип транспорта
	tVid = TransportVid::centaur;		// Кентавр
	tRaces.insert(RaceType::ground);	// Разрешаем участие в наземной гонке
	tRaces.insert(RaceType::combined);	// Разрешаем участие в комбинированной гонке
	tV = 15;							// Скорость транспортного средства
	DrivingTime = 8.0;					// Время движения до отдыха
	RestTime = 2.0;						// Длительность отдыха	
}

// Рассчитываем время прохождения дистанции 
void Centaur::Calc(int distance) {
	tDistance = distance;								// Запоминаем дистанцию
	double t1 = std::round(tDistance / tV * 10) / 10;	// Время прохождения дистанции без отдыха. Время округляем до 1 знака после запятой
	int rest_count = t1 / DrivingTime;					// Количество остановок
	tTime = t1 + rest_count * RestTime;					// Время в пути c остановками	
}

