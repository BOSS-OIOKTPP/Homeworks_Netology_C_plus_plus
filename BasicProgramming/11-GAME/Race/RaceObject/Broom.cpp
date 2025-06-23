#include <cmath>
#include "Broom.h"

// Метла
Broom::Broom() {
	tType = TransportType::air;			// Воздушный тип транспорта
	tVid = TransportVid::broom;			// Метла
	tRaces.insert(RaceType::air);		// Разрешаем участие в воздушной гонке
	tRaces.insert(RaceType::combined);	// Разрешаем участие в комбинированной гонке
	tV = 20;							// Скорость транспортного средства
}

// Процент сокращения расстояния
// Увеличивается на 1 % за каждую 1000 у.е.расстояния
// Например, для расстояния 5600 коэффициент будет 5 %
int Broom::Procent(int distance) { return distance / 1000; };

// Рассчитываем время прохождения дистанции 
void Broom::Calc(int distance) {
	tDistance = distance*(100-Procent(distance))/100;	// Запоминаем дистанцию
	tTime = std::round(tDistance / tV * 10) / 10;		// Время прохождения дистанции. Время округляем до 1 знака после запятой	
}