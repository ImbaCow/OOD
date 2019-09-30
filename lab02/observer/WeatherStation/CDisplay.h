#pragma once
#include "pch.h"
#include "CWeatherData.h"

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override;
};
