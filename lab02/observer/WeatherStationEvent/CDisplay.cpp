#pragma once
#include "pch.h"
#include "CDisplay.h"

void CDisplay::Update(SWeatherProInfo const& data)
{
	std::cout << "---Current Info---" << std::endl;
	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "------------------" << std::endl;
}
