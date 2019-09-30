#pragma once
#include "pch.h"
#include "CDisplay.h"

CDisplay::CDisplay(const CWeatherData& inData, const CWeatherData& outData)
	: inData(inData)
	, outData(outData)
{
}

void CDisplay::Update(const CWeatherData& data)
{
	std::cout << "---Current Info---" << std::endl;
	std::cout << "Source type " << DataTypeToStr(data) << std::endl;
	std::cout << "Current Temp " << data.GetTemperature() << std::endl;
	std::cout << "Current Hum " << data.GetHumidity() << std::endl;
	std::cout << "Current Pressure " << data.GetPressure() << std::endl;
	std::cout << "------------------" << std::endl;
}

std::string CDisplay::DataTypeToStr(const CWeatherData& data)
{
	if (&data == &inData)
	{
		return "in";
	}
	else if (&data == &outData)
	{
		return "out";
	}

	throw std::invalid_argument("Unhandled wather data type");
}
