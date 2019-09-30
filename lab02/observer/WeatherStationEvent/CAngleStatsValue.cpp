#pragma once
#include "pch.h"
#include "CAngleStatsValue.h"

double NormalizeAngle(double number)
{
	while (number < 0)
	{
		number += 360;
	}
	while (number >= 360)
	{
		number -= 360;
	}

	return number;
}

void CAngleStatsValue::AddValue(double value)
{
	value = NormalizeAngle(value);
	bool isTopAngle = m_count == 0 || std::abs(m_avgSum - value) <= 180;
	m_avgSum = (m_avgSum * m_count + value) / (m_count + 1);
	if (!isTopAngle)
	{
		m_avgSum += 180;
	}
	++m_count;
}

std::optional<double> CAngleStatsValue::GetAvgValue()
{
	if (m_count == 0)
	{
		return std::nullopt;
	}
	return m_avgSum;
}
