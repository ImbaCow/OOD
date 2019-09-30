#pragma once
#include "pch.h"

class CStatsValue
{
public:
	void AddValue(double value);
	std::optional<double> GetMinValue();
	std::optional<double> GetMaxValue();
	std::optional<double> GetAvgValue();

private:
	double m_sum = 0;
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	size_t m_count = 0;
};