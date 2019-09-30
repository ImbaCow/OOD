#pragma once
#include "pch.h"

class CStatsValue
{
public:
	void AddValue(double value);
	std::optional<double> GetMinValue();
	std::optional<double> GetMaxValue();
	std::optional<double> GetAvgValue();

	static std::string StatsToString(std::optional<double> statsValue)
	{
		return statsValue ? std::to_string(statsValue.value()) : "undefined";
	}

private:
	double m_sum = 0;
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	size_t m_count = 0;
};