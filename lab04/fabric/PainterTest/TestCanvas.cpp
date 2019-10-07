#include "pch.h"
#include "TestCanvas.h"

void TestCanvas::SetColor(Color color)
{
	m_color = color;
}

void TestCanvas::DrawLine(const Point& from, const Point& to)
{
	m_lineArr.push_back({ from, to });
}

void TestCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	m_ellipseArr.push_back({ leftTop, width, height });
}
