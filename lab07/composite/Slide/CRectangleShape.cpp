#include "pch.h"
#include "CRectangleShape.h"

Rect CalcRectangleFrame(const Point& leftTop, double width, double height)
{
	return {
		leftTop,
		width,
		height
	};
};

CRectangleShape::CRectangleShape(const Point& leftTop, double width, double height)
	: CShape(CalcRectangleFrame(leftTop, width, height))
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CRectangleShape::Draw(const ICanvas& canvas)
{
}

void CRectangleShape::ResizeShape(const Rect& newRect)
{
	m_leftTop = newRect.leftTop;
	m_width = newRect.width;
	m_height = newRect.height;
}
