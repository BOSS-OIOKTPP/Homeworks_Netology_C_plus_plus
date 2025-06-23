#pragma once

#include "Transport.h"

// Ботинки-вездеходы
class Boots: public Transport
{ 
private:
	double DrivingTime;		// Время движения до отдыха
	double RestTime1;		// Длительность отдыха первый раз
	double RestTime2;		// Длительность отдыха все последующие разы
public:
	Boots();

	void Calc(int distance) override;
};
