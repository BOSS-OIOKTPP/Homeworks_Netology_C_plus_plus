#include "Eagle.h"

// Орел
Eagle::Eagle() {
	tType = TransportType::air;		// Воздушный тип транспорта
	tVid = TransportVid::eagle;		// Орел
	tV = 8;							// Скорость транспортного средства
	Procent = 6;
}

// Рассчитываем время прохождения дистанции 
void Eagle::Calc(int distance) {
	tDistance = distance * (100 - Procent)/100;	// Запоминаем дистанцию
	tTime = tDistance / tV;						// Время прохождения дистанции	
}
