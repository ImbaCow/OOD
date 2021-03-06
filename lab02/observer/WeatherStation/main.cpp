#include "pch.h"
#include "WeatherStation.h"

int main()
{
	CWeatherData data;
	WeatherStation ws;

	ws.GetData().SetMeasurements(3, 0.7, 760);
	ws.GetData().SetMeasurements(4, 0.8, 761);

	ws.GetData().SetMeasurements(10, 0.8, 761);
	ws.GetData().SetMeasurements(-10, 0.8, 761);
	system("pause");
	return 0;
}