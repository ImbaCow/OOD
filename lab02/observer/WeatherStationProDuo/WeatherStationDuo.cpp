#include "pch.h"
#include "WeatherStationDuo.h"

WeatherStationDuo::WeatherStationDuo()
{
	inSubject.RegisterObserver(statsDisplay, 1);
	inSubject.RegisterObserver(display, 2);

	outSubject.RegisterObserver(statsDisplayPro, 2);
	outSubject.RegisterObserver(displayPro, 1);
}

WeatherStationDuo::~WeatherStationDuo()
{
	inSubject.RemoveObserver(statsDisplay);
	inSubject.RemoveObserver(display);

	outSubject.RemoveObserver(statsDisplayPro);
	outSubject.RemoveObserver(displayPro);
}

CWeatherData& WeatherStationDuo::GetInData()
{
	return inSubject;
}

CWeatherDataPro& WeatherStationDuo::GetOutData()
{
	return outSubject;
}
