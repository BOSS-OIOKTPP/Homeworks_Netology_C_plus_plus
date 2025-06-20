#pragma once
#include "Transport.h"

// Орел
class Eagle : public Transport
{
private:
	int Procent; // Процент сокращения расстояния
public:
	Eagle();

	void Calc(int distance) override;
};

