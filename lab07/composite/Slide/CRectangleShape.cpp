#include "pch.h"
#include "CRectangleShape.h"

CRectangleShape::CRectangleShape(const Rect& frame, std::shared_ptr<IStyle> fillStyle, std::shared_ptr<ILineStyle> lineStyle)
	: CShape(frame, fillStyle, lineStyle)
	, m_leftTop(frame.leftTop)
	, m_width(frame.width)
	, m_height(frame.height)
{
}

Point CRectangleShape::GetLeftTop()
{
	return m_leftTop;
}

double CRectangleShape::GetWidth()
{
	return m_width;
}

double CRectangleShape::GetHeight()
{
	return m_height;
}

void CRectangleShape::ResizeShape(const Rect& newRect)
{
	m_leftTop = newRect.leftTop;
	m_width = newRect.width;
	m_height = newRect.height;
}

void CRectangleShape::DrawColoredLine(ICanvas& canvas)
{
	Point rightTop{ m_leftTop.x + m_width, m_leftTop.y };
	Point rightBottom{ m_leftTop.x + m_width, m_leftTop.y + m_height };
	Point leftBottom{ m_leftTop.x, m_leftTop.y + m_height };

	canvas.DrawLine(m_leftTop, rightTop);
	canvas.DrawLine(rightTop, rightBottom);
	canvas.DrawLine(rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, m_leftTop);
}

void CRectangleShape::DrawColoredFill(ICanvas& canvas)
{
	Point rightTop{ m_leftTop.x + m_width, m_leftTop.y };
	Point rightBottom{ m_leftTop.x + m_width, m_leftTop.y + m_height };
	Point leftBottom{ m_leftTop.x, m_leftTop.y + m_height };

	canvas.FillPolygon({ rightTop, rightBottom, leftBottom, m_leftTop });
}
