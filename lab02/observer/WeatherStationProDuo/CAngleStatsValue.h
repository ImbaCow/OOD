#pragma once
#include "pch.h"

class CAngleStatsValue
{
public:
	void AddValue(double value);
	std::optional<double> GetAvgValue();

	static std::string StatsToString(std::optional<double> statsValue)
	{
		return statsValue ? std::to_string(statsValue.value()) : "undefined";
	}

private:
	double m_avgSum = 0;
	size_t m_count = 0;
};