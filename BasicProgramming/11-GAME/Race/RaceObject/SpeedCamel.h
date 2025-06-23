#pragma once
#include "Transport.h"

// Верблюд-скороход
class SpeedCamel :  public Transport
{
private:
	double DrivingTime;	// Время движения до отдыха
	double RestTime1;		// Длительность отдыха первый раз
	double RestTime2;		// Длительность отдыха во второй раз
	double RestTime3;		// Длительность отдыха все последующие разы
public:
	SpeedCamel();

	void Calc(int distance) override;
};

