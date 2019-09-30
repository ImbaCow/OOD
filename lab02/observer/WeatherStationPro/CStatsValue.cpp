#include "pch.h"
#include "CStatsValue.h"

void CStatsValue::AddValue(double value)
{
	m_sum += value;
	m_min = std::min(value, m_min);
	m_max = std::max(value, m_max);
	++m_count;
}

std::optional<double> CStatsValue::GetMinValue()
{
	if (m_count == 0)
	{
		return std::nullopt;
	}
	return m_min;
}

std::optional<double> CStatsValue::GetMaxValue()
{
	if (m_count == 0)
	{
		return std::nullopt;
	}
	return m_max;
}

std::optional<double> CStatsValue::GetAvgValue()
{
	if (m_count == 0)
	{
		return std::nullopt;
	}
	return m_sum / m_count;
}