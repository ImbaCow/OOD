#include "pch.h"
#include "CLineStyleGroup.h"
#include "CompositeUtils.h"

CLineStyleGroup::CLineStyleGroup(const std::vector<std::shared_ptr<ILineStyle>>& styleArr)
	: m_styleArr(styleArr)
{
}

std::optional<bool> CLineStyleGroup::IsEnabled() const
{
	return GetCompositeValue(m_styleArr, &ILineStyle::IsEnabled);
}

void CLineStyleGroup::Enable(bool enable)
{
	SetCompositeValue(m_styleArr, &ILineStyle::Enable, enable);
}

std::optional<RGBAColor> CLineStyleGroup::GetColor() const
{
	return GetCompositeValue(m_styleArr, &ILineStyle::GetColor);
}

void CLineStyleGroup::SetColor(RGBAColor color)
{
	SetCompositeValue(m_styleArr, &ILineStyle::SetColor, color);
}

std::optional<double> CLineStyleGroup::GetLineSize() const
{
	return GetCompositeValue(m_styleArr, &ILineStyle::GetLineSize);
}

void CLineStyleGroup::SetLineSize(double lineSize)
{
	SetCompositeValue(m_styleArr, &ILineStyle::SetLineSize, lineSize);
}
