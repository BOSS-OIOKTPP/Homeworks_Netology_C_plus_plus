#pragma once
#include "Transport.h"

// Верблюд
class Camel : public Transport
{
private:
	double DrivingTime;		// Время движения до отдыха
	double RestTime1;		// Длительность отдыха первый раз
	double RestTime2;		// Длительность отдыха все последующие разы
public:
	Camel();

	void Calc(int distance) override;
};


