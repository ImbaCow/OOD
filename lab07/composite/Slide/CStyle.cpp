#include "pch.h"
#include "CStyle.h"

CStyle::CStyle()
{
}

CStyle::CStyle(RGBAColor color)
	: m_isEnabled(true)
	, m_color(color)
{
}

bool CStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

std::optional<RGBAColor> CStyle::GetColor() const
{
	if (!IsEnabled())
	{
		throw std::logic_error("Style is not enabled");
	}
	return m_color;
}

void CStyle::SetColor(RGBAColor color)
{
	m_color = color;
}
