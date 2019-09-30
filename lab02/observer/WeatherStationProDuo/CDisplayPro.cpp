#pragma once
#include "pch.h"
#include "CDisplayPro.h"

void CDisplayPro::Update(const CWeatherDataPro& data)
{
	std::cout << "---Current Info---" << std::endl;
	std::cout << "Source type outside" << std::endl;
	std::cout << "Current Temp " << data.GetTemperature() << std::endl;
	std::cout << "Current Hum " << data.GetHumidity() << std::endl;
	std::cout << "Current Pressure " << data.GetPressure() << std::endl;
	std::cout << "Current Wind Speed " << data.GetWindSpeed() << std::endl;
	std::cout << "Current Wind Angle " << data.GetWindAngle() << std::endl;
	std::cout << "------------------" << std::endl;
}
