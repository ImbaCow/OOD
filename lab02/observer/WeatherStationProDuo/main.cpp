#pragma once
#include "pch.h"
#include "WeatherStationDuo.h"

int main()
{
	WeatherStationDuo ws;

	ws.GetInData().SetMeasurements(3, 0.7, 760);
	ws.GetInData().SetMeasurements(4, 0.8, 761);

	ws.GetOutData().SetMeasurements(10, 0.8, 761, 123, 87);
	ws.GetOutData().SetMeasurements(-10, 0.8, 761, 127, 982);
	system("pause");
	return 0;
}