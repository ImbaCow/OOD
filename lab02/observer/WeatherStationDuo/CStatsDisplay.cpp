#pragma once
#include "pch.h"
#include "CStatsDisplay.h"

CStatsDisplay::CStatsDisplay(const CWeatherData& inData, const CWeatherData& outData)
	: inData(inData)
	, outData(outData)
{
}

std::string StatsToString(std::optional<double> statsValue)
{
	return statsValue ? std::to_string(statsValue.value()) : "undefined";
}

void CStatsDisplay::Update(const CWeatherData& data)
{
	m_temperatureStats.AddValue(data.GetTemperature());
	m_humidityStats.AddValue(data.GetHumidity());
	m_pressureStats.AddValue(data.GetPressure());

	std::cout << "------Stats------" << std::endl;
	std::cout << "Source type " << DataTypeToStr(data) << std::endl;
	std::cout << "Max Temp " << StatsToString(m_temperatureStats.GetMaxValue()) << std::endl;
	std::cout << "Min Temp " << StatsToString(m_temperatureStats.GetMinValue()) << std::endl;
	std::cout << "Average Temp " << StatsToString(m_temperatureStats.GetAvgValue()) << std::endl;

	std::cout << "Max Humidity " << StatsToString(m_humidityStats.GetMaxValue()) << std::endl;
	std::cout << "Min Humidity " << StatsToString(m_humidityStats.GetMinValue()) << std::endl;
	std::cout << "Average Humidity " << StatsToString(m_humidityStats.GetAvgValue()) << std::endl;

	std::cout << "Max Pressure " << StatsToString(m_pressureStats.GetMaxValue()) << std::endl;
	std::cout << "Min Pressure " << StatsToString(m_pressureStats.GetMinValue()) << std::endl;
	std::cout << "Average Pressure " << StatsToString(m_pressureStats.GetAvgValue()) << std::endl;
	std::cout << "-----------------" << std::endl;
}

std::string CStatsDisplay::DataTypeToStr(const CWeatherData& data)
{
	if (&data == &inData)
	{
		return "in";
	}
	else if (&data == &outData)
	{
		return "out";
	}

	throw std::invalid_argument("Unhandled wather data type");
}
