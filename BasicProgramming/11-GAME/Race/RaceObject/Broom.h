#pragma once
#include "Transport.h"

// Метла
class Broom : public Transport
{
private:
	// Процент сокращения расстояния
	// Увеличивается на 1 % за каждую 1000 у.е.расстояния
	// Например, для расстояния 5600 коэффициент будет 5 %
	int Procent(int distance);
public:
	Broom();

	void Calc(int distance) override;
};