#pragma once
#include "pch.h"
#include "CStatsValue.h"
#include "CAngleStatsValue.h"
#include "CWeatherDataPro.h"

class CStatsDisplay : public IObserver<SWeatherProInfo>
{
private:
	void Update(SWeatherProInfo const& data) override;

	CStatsValue m_temperatureStats;
	CStatsValue m_humidityStats;
	CStatsValue m_pressureStats;
	CStatsValue m_windSpeed;
	CAngleStatsValue m_windAngle;
};
