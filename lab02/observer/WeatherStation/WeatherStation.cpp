#include "pch.h"
#include "WeatherStation.h"

WeatherStation::WeatherStation()
{
	subject.RegisterObserver(statsDisplay, 1);
	subject.RegisterObserver(display, 2);
}

WeatherStation::~WeatherStation()
{
	subject.RemoveObserver(statsDisplay);
	subject.RemoveObserver(display);
}

CWeatherData& WeatherStation::GetData()
{
	return subject;
}
