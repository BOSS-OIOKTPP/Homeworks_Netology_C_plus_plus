#include <cmath>
#include "Eagle.h"

// Орел
Eagle::Eagle() {
	tType = TransportType::air;			// Воздушный тип транспорта
	tVid = TransportVid::eagle;			// Орел
	tRaces.insert(RaceType::air);		// Разрешаем участие в воздушной гонке
	tRaces.insert(RaceType::combined);	// Разрешаем участие в комбинированной гонке
	tV = 8;								// Скорость транспортного средства
	Procent = 6;
}

// Рассчитываем время прохождения дистанции 
void Eagle::Calc(int distance) {
	tDistance = distance * (100 - Procent)/100;		// Запоминаем дистанцию	
	tTime = std::round(tDistance / tV * 10) / 10;	// Время прохождения дистанции. Время округляем до 1 знака после запятой	
}
