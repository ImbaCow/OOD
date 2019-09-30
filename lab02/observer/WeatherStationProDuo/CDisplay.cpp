#pragma once
#include "pch.h"
#include "CDisplay.h"

void CDisplay::Update(const CWeatherData& data)
{
	std::cout << "---Current Info---" << std::endl;
	std::cout << "Source type inside " << std::endl;
	std::cout << "Current Temp " << data.GetTemperature() << std::endl;
	std::cout << "Current Hum " << data.GetHumidity() << std::endl;
	std::cout << "Current Pressure " << data.GetPressure() << std::endl;
	std::cout << "------------------" << std::endl;
}
