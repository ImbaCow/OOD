#pragma once
#include "pch.h"
#include "WeatherStationDuo.h"

int main()
{
	WeatherStationDuo ws;

	ws.GetInData().SetMeasurements(3, 0.7, 760);
	ws.GetInData().SetMeasurements(5, 1.7, 7660);
	ws.GetOutData().SetMeasurements(4, 0.8, 761);
	system("pause");
	return 0;
}