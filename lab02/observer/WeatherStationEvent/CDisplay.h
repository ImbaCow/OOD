#pragma once
#include "pch.h"
#include "CWeatherDataPro.h"

class CDisplay : public IObserver<SWeatherProInfo>
{
private:
	void Update(SWeatherProInfo const& data) override;
};
