#pragma once
#include "pch.h"
#include "CWeatherDataPro.h"

class CDisplayPro : public IObserver<const CWeatherDataPro&>
{
private:
	void Update(const CWeatherDataPro& data) override;
};
