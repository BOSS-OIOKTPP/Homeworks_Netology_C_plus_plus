#pragma once
#include "Transport.h"

// Ковер-самолет
class FlyingCarpet : public Transport
{
private:
	// Процент сокращения расстояния
	// Если расстояние меньше 1000 — без сокращения
	// Если расстояние меньше 5000 — 3 %
	// Если расстояние меньше 10000 — 10 %
	// Если расстояние больше или равно 10000 — 5 %
	int Procent(int distance);
public:
	FlyingCarpet();

	void Calc(int distance) override;
};

