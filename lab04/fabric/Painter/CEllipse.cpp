#pragma once 
#include "pch.h"
#include "CEllipse.h"

CEllipse::CEllipse(Color color, const Point& leftTop, double width, double height)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}
void CEllipse::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawEllipse(m_leftTop, m_width, m_height);
}

Point CEllipse::GetLeftTop() const
{
	return m_leftTop;
}

double CEllipse::GetWidth() const
{
	return m_width;
}

double CEllipse::GetHeight() const
{
	return m_height;
}
