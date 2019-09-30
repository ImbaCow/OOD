#pragma once
#include "CWeatherData.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

class WeatherStationDuo
{
public:
	WeatherStationDuo();
	~WeatherStationDuo();

	CWeatherData& GetInData();
	CWeatherData& GetOutData();

private:
	CWeatherData inSubject;
	CWeatherData outSubject;

	CStatsDisplay statsDisplay;
	CDisplay display;
};
