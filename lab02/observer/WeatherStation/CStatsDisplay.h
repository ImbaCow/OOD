#pragma once
#include "pch.h"
#include "CStatsValue.h"
#include "CWeatherData.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override;

	CStatsValue m_temperatureStats;
	CStatsValue m_humidityStats;
	CStatsValue m_pressureStats;
};
