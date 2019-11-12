#include "pch.h"
#include "CStyleGroup.h"
#include "CompositeUtils.h"

CStyleGroup::CStyleGroup(const std::vector<std::shared_ptr<IStyle>>& styleArr)
	: m_styleArr(styleArr)
{
}

std::optional<bool> CStyleGroup::IsEnabled() const
{
	return GetCompositeValue(m_styleArr, &IStyle::IsEnabled);
}

void CStyleGroup::Enable(bool enable)
{
	SetCompositeValue(m_styleArr, &IStyle::Enable, enable);
}

std::optional<RGBAColor> CStyleGroup::GetColor() const
{
	return GetCompositeValue(m_styleArr, &IStyle::GetColor);
}

void CStyleGroup::SetColor(RGBAColor color)
{
	SetCompositeValue(m_styleArr, &IStyle::SetColor, color);
}
