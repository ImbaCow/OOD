#pragma once
#include "CWeatherData.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

class WeatherStation
{
public:
	WeatherStation();
	~WeatherStation();

	CWeatherData& GetData();

private:
	CWeatherData subject;
	CStatsDisplay statsDisplay;
	CDisplay display;
};
