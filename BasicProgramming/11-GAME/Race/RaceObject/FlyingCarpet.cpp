#include <cmath>
#include "FlyingCarpet.h"

// Ковер-самолет
FlyingCarpet::FlyingCarpet() {
	tType = TransportType::air;				// Воздушный тип транспорта
	tVid = TransportVid::flying_carpet;		// Ковер-самолет
	tRaces.insert(RaceType::air);			// Разрешаем участие в воздушной гонке
	tRaces.insert(RaceType::combined);		// Разрешаем участие в комбинированной гонке
	tV = 10;								// Скорость транспортного средства
}

// Процент сокращения расстояния
// Если расстояние меньше 1000 — без сокращения
// Если расстояние меньше 5000 — 3 %
// Если расстояние меньше 10000 — 10 %
// Если расстояние больше или равно 10000 — 5 %
int FlyingCarpet::Procent(int distance) { 
	if (distance < 1000) {
		return 0;
    }
	else if (distance < 5000) {
		return 3;
	}
	if (distance < 10000) {
		return 10;
	}
	else 
		return 5;
}

// Рассчитываем время прохождения дистанции 
void FlyingCarpet::Calc(int distance) {
	tDistance = distance * (100 - Procent(distance)) / 100;	// Запоминаем дистанцию
	tTime = std::round(tDistance / tV * 10) / 10;			// Время прохождения дистанции без отдыха. Время округляем до 1 знака после запятой
}