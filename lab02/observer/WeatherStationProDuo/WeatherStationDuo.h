#pragma once
#include "CWeatherData.h"
#include "CWeatherDataPro.h"
#include "CDisplay.h"
#include "CDisplayPro.h"
#include "CStatsDisplay.h"
#include "CStatsDisplayPro.h"

class WeatherStationDuo
{
public:
	WeatherStationDuo();
	~WeatherStationDuo();

	CWeatherData& GetInData();
	CWeatherDataPro& GetOutData();

private:
	CWeatherData inSubject;
	CWeatherDataPro outSubject;

	CStatsDisplay statsDisplay;
	CDisplay display;

	CStatsDisplayPro statsDisplayPro;
	CDisplayPro displayPro;
};
