#pragma once
#include "Transport.h"

// Верблюд-скороход
class SpeedCamel :  public Transport
{
private:
	int DrivingTime;	// Время движения до отдыха
	int RestTime1;		// Длительность отдыха первый раз
	int RestTime2;		// Длительность отдыха во второй раз
	int RestTime3;		// Длительность отдыха все последующие разы
public:
	SpeedCamel();

	void Calc(int distance) override;
};

