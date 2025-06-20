#pragma once

#include "Transport.h"

// Ботинки-вездеходы
class Boots: public Transport
{ 
private:
	int DrivingTime;	// Время движения до отдыха
	int RestTime1;		// Длительность отдыха первый раз
	int RestTime2;		// Длительность отдыха все последующие разы
public:
	Boots();

	void Calc(int distance) override;
};
