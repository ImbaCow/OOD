#pragma once 
#include "pch.h"
#include "CRegularPolygon.h"

CRegularPolygon::CRegularPolygon(Color color, size_t vertexCount, const Point& center, double radius)
	: CShape(color)
	, m_vertexCount(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
	if (m_vertexCount < 3)
	{
		throw std::invalid_argument("vertex count too smol");
	}
}

size_t CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

Point CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}

Point CRegularPolygon::GetVertexByIndex(size_t index) const
{
	double x = m_center.first + m_radius * std::cos(PI / 2 + (2 * PI * index) / m_vertexCount);
	double y = m_center.second + m_radius * std::sin(PI / 2 + (2 * PI * index) / m_vertexCount);
	return { x, y };
}

void CRegularPolygon::Draw(std::shared_ptr<ICanvas>& canvas) const
{
	canvas->SetColor(GetColor());
	for (size_t i = 0; i < m_vertexCount; ++i)
	{
		Point from = GetVertexByIndex(i);
		Point to = GetVertexByIndex(i + 1);
		canvas->DrawLine(from, to);
	}
}
