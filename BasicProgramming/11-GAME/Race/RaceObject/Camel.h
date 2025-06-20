#pragma once
#include "Transport.h"

class Camel : public Transport
{
private:
	int DrivingTime;	// Время движения до отдыха
	int RestTime1;		// Длительность отдыха первый раз
	int RestTime2;		// Длительность отдыха все последующие разы
public:
	Camel();

	void Calc(int distance) override;
};


