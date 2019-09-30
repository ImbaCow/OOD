#pragma once
#include "pch.h"
#include "CStatsDisplayPro.h"

void CStatsDisplayPro::Update(const CWeatherDataPro& data)
{
	m_temperatureStats.AddValue(data.GetTemperature());
	m_humidityStats.AddValue(data.GetHumidity());
	m_pressureStats.AddValue(data.GetPressure());
	m_windSpeed.AddValue(data.GetWindSpeed());
	m_windAngle.AddValue(data.GetWindAngle());

	std::cout << "------Stats------" << std::endl;
	std::cout << "Source type outside" << std::endl;
	std::cout << "Max Temp " << CStatsValue::StatsToString(m_temperatureStats.GetMaxValue()) << std::endl;
	std::cout << "Min Temp " << CStatsValue::StatsToString(m_temperatureStats.GetMinValue()) << std::endl;
	std::cout << "Average Temp " << CStatsValue::StatsToString(m_temperatureStats.GetAvgValue()) << std::endl;

	std::cout << "Max Humidity " << CStatsValue::StatsToString(m_humidityStats.GetMaxValue()) << std::endl;
	std::cout << "Min Humidity " << CStatsValue::StatsToString(m_humidityStats.GetMinValue()) << std::endl;
	std::cout << "Average Humidity " << CStatsValue::StatsToString(m_humidityStats.GetAvgValue()) << std::endl;

	std::cout << "Max Pressure " << CStatsValue::StatsToString(m_pressureStats.GetMaxValue()) << std::endl;
	std::cout << "Min Pressure " << CStatsValue::StatsToString(m_pressureStats.GetMinValue()) << std::endl;
	std::cout << "Average Pressure " << CStatsValue::StatsToString(m_pressureStats.GetAvgValue()) << std::endl;

	std::cout << "Max Wind Speed " << CStatsValue::StatsToString(m_windSpeed.GetMaxValue()) << std::endl;
	std::cout << "Min Wind Speed " << CStatsValue::StatsToString(m_windSpeed.GetMinValue()) << std::endl;
	std::cout << "Average Wind Speed " << CStatsValue::StatsToString(m_windSpeed.GetAvgValue()) << std::endl;

	std::cout << "Average Wind Angle " << CAngleStatsValue::StatsToString(m_windAngle.GetAvgValue()) << std::endl;
	std::cout << "-----------------" << std::endl;
}
