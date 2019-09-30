#pragma once
#include "pch.h"
#include "CWeatherData.h"

class CDisplay : public IObserver<const CWeatherData&>
{
public:
	CDisplay(const CWeatherData& inData, const CWeatherData& outData);

private:
	const CWeatherData& inData;
	const CWeatherData& outData;

	void Update(const CWeatherData& data) override;
	std::string DataTypeToStr(const CWeatherData& data);
};
