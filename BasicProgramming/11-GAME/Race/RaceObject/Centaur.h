#pragma once
#include "Transport.h"

// Кентавр
class Centaur : public Transport
{
private:
	double DrivingTime;	// Время движения до отдыха
	double RestTime; 		// Длительность отдыха	
public:
	Centaur();

	void Calc(int distance) override;
};

