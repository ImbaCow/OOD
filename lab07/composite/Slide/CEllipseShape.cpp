#include "pch.h"
#include "CEllipseShape.h"

CEllipseShape::CEllipseShape(const Rect& frame, std::shared_ptr<IStyle> fillStyle, std::shared_ptr<ILineStyle> lineStyle)
	: CShape(frame, fillStyle, lineStyle)
	, m_leftTop(frame.leftTop)
	, m_width(frame.width)
	, m_height(frame.height)
{
}

Point CEllipseShape::GetLeftTop()
{
	return m_leftTop;
}

double CEllipseShape::GetWidth()
{
	return m_width;
}

double CEllipseShape::GetHeight()
{
	return m_height;
}

void CEllipseShape::ResizeShape(const Rect& newRect)
{
	m_leftTop = newRect.leftTop;
	m_width = newRect.width;
	m_height = newRect.height;
}

void CEllipseShape::DrawColoredLine(ICanvas& canvas)
{
	canvas.DrawEllipse(m_leftTop, m_width, m_height);
}

void CEllipseShape::DrawColoredFill(ICanvas& canvas)
{
	canvas.FillEllipse(m_leftTop, m_width, m_height);
}
