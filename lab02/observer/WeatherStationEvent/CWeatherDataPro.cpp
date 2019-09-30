#pragma once
#include "pch.h"
#include "CWeatherDataPro.h"

double CWeatherDataPro::GetTemperature() const
{
	return m_temperature;
}

double CWeatherDataPro::GetHumidity() const
{
	return m_humidity;
}

double CWeatherDataPro::GetPressure() const
{
	return m_pressure;
}

double CWeatherDataPro::GetWindSpeed() const
{
	return m_windSpeed;
}

double CWeatherDataPro::GetWindAngle() const
{
	return m_windAngle;
}

void CWeatherDataPro::MeasurementsChanged()
{
	NotifyObservers();
}

void CWeatherDataPro::SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windAngle)
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;
	m_windSpeed = windSpeed;
	m_windAngle = windAngle;

	MeasurementsChanged();
}

SWeatherProInfo CWeatherDataPro::GetChangedData() const
{
	SWeatherProInfo info;
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	info.windSpeed = GetWindSpeed();
	info.windAngle = GetWindAngle();
	return info;
}
