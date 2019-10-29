#include "pch.h"
#include "CEllipseShape.h"

Rect CalcEllipseFrame(const Point& leftTop, double width, double height)
{
	return {
		leftTop,
		width,
		height
	};
};

CEllipseShape::CEllipseShape(const Point& leftTop, double width, double height)
	: CShape(CalcEllipseFrame(leftTop, width, height))
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CEllipseShape::Draw(const ICanvas& canvas)
{
}

void CEllipseShape::ResizeShape(const Rect& newRect)
{
	m_leftTop = newRect.leftTop;
	m_width = newRect.width;
	m_height = newRect.height;
}
