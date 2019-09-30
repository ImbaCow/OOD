#pragma once
#include "pch.h"
#include "CWeatherData.h"

class CDisplay : public IObserver<const CWeatherData&>
{
private:
	void Update(const CWeatherData& data) override;
};
