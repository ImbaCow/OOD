#include "pch.h"
#include "WeatherStationDuo.h"

WeatherStationDuo::WeatherStationDuo()
	: statsDisplay(this->inSubject, this->outSubject)
	, display(this->inSubject, this->outSubject)
{
	this->inSubject.RegisterObserver(statsDisplay, 1);
	this->inSubject.RegisterObserver(display, 2);
	this->outSubject.RegisterObserver(statsDisplay, 2);
	this->outSubject.RegisterObserver(display, 1);
}

WeatherStationDuo::~WeatherStationDuo()
{
	inSubject.RemoveObserver(statsDisplay);
	inSubject.RemoveObserver(display);
	outSubject.RemoveObserver(statsDisplay);
	outSubject.RemoveObserver(display);
}

CWeatherData& WeatherStationDuo::GetInData()
{
	return inSubject;
}

CWeatherData& WeatherStationDuo::GetOutData()
{
	return outSubject;
}
