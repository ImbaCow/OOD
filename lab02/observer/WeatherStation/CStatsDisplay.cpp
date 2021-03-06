#pragma once
#include "pch.h"
#include "CStatsDisplay.h"

std::string StatsToString(std::optional<double> statsValue)
{
	return statsValue ? std::to_string(statsValue.value()) : "undefined";
}

void CStatsDisplay::Update(SWeatherInfo const& data)
{
	m_temperatureStats.AddValue(data.temperature);
	m_humidityStats.AddValue(data.humidity);
	m_pressureStats.AddValue(data.pressure);

	std::cout << "------Stats------" << std::endl;
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
