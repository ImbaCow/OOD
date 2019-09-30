#pragma once
#include "pch.h"
#include "CWeatherData.h"
#include "CStatsValue.h"

class CStatsDisplay : public IObserver<const CWeatherData&>
{
public:
	CStatsDisplay(const CWeatherData& inData, const CWeatherData& outData);

private:
	const CWeatherData& inData;
	const CWeatherData& outData;

	void Update(const CWeatherData& data) override;
	std::string DataTypeToStr(const CWeatherData& data);

	CStatsValue m_temperatureStats;
	CStatsValue m_humidityStats;
	CStatsValue m_pressureStats;
};
