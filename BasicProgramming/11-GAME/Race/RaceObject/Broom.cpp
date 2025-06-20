#include "Broom.h"

// Метла
Broom::Broom() {
	tType = TransportType::air;		// Воздушный тип транспорта
	tVid = TransportVid::broom;		// Метла
	tV = 20;						// Скорость транспортного средства
}

// Процент сокращения расстояния
// Увеличивается на 1 % за каждую 1000 у.е.расстояния
// Например, для расстояния 5600 коэффициент будет 5 %
int Broom::Procent(int distance) { return distance / 1000; };

// Рассчитываем время прохождения дистанции 
void Broom::Calc(int distance) {
	tDistance = distance*(100-Procent(distance))/100;	// Запоминаем дистанцию
	tTime = tDistance / tV;								// Время прохождения дистанции	
}