#include "pch.h"
#include "CShape.h"

CShape::CShape(const Rect& rect)
	: m_frame(rect)
{
}

Rect CShape::GetFrame()
{
	return m_frame;
}

void CShape::SetFrame(const Rect& rect)
{
	ResizeShape(rect);
	m_frame = rect;
}

ILineStyle& CShape::GetOutlineStyle()
{
	return m_lineStyle;
}

const ILineStyle& CShape::GetOutlineStyle() const
{
	return m_lineStyle;
}

IStyle& CShape::GetFillStyle()
{
	return m_fillStyle;
}

const IStyle& CShape::GetFillStyle() const
{
	return m_fillStyle;
}
