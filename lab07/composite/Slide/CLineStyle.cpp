#include "pch.h"
#include "CLineStyle.h"

CLineStyle::CLineStyle()
	: CStyle()
{
}

CLineStyle::CLineStyle(RGBAColor color, double lineSize)
	: CStyle(color)
	, m_lineSize(lineSize)
{
}

std::optional<double> CLineStyle::GetLineSize() const
{
	if (!CStyle::IsEnabled().value())
	{
		throw std::logic_error("Style is not enabled");
	}
	return m_lineSize;
}

void CLineStyle::SetLineSize(double lineSize)
{
	m_lineSize = lineSize;
}
	
std::optional<bool> CLineStyle::IsEnabled() const
{
	return CStyle::IsEnabled();
}

void CLineStyle::Enable(bool enable)
{
	CStyle::Enable(enable);
}

std::optional<RGBAColor> CLineStyle::GetColor() const
{
	return CStyle::GetColor();
}

void CLineStyle::SetColor(RGBAColor color)
{
	CStyle::SetColor(color);
}
