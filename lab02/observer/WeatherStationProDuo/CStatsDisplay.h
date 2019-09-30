#pragma once
#include "pch.h"
#include "CStatsValue.h"
#include "CWeatherData.h"

class CStatsDisplay : public IObserver<const CWeatherData&>
{
private:
	void Update(const CWeatherData& data) override;

	CStatsValue m_temperatureStats;
	CStatsValue m_humidityStats;
	CStatsValue m_pressureStats;
};
