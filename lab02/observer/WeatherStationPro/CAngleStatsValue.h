#pragma once
#include "pch.h"

class CAngleStatsValue
{
public:
	void AddValue(double value);
	std::optional<double> GetAvgValue();

private:
	double m_avgSum = 0;
	size_t m_count = 0;
};