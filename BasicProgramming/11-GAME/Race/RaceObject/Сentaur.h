#pragma once
#include "Transport.h"

// Кентавр
class Centaur : public Transport
{
private:
	int DrivingTime;	// Время движения до отдыха
	int RestTime; 		// Длительность отдыха	
public:
	Centaur();

	void Calc(int distance) override;
};

