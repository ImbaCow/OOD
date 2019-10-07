#pragma once 
#include "pch.h"
#include "CCanvas.h"

CCanvas::CCanvas(std::ostream& stream)
	: m_stream(stream)
{
}

void CCanvas::SetColor(Color color)
{
	m_color = color;
}

void CCanvas::DrawLine(const Point& from, const Point& to)
{
	m_stream << "line; color: " << m_color
			 << "; from: {" << from.first << "," << from.second
			 << "}; to: {" << to.first << "," << to.second << "};" << std::endl;
}

void CCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	m_stream << "ellipse; color: " << m_color
			 << "; leftTop: {" << leftTop.first << "," << leftTop.second
			 << "}; width: " << width << "; height: " << height << ";" << std::endl;
}
