#pragma once
#include "pch.h"
#include "ICanvas.h"
#include "simple_svg_1.0.0.hpp"

class CSvgCanvas : public ICanvas
{
public:
	CSvgCanvas(const std::string& fileName, double width, double height, double lineWidth);
	virtual ~CSvgCanvas();

	virtual void SetColor(Color color) override;
	virtual void DrawLine(const Point& from, const Point& to) override;
	virtual void DrawEllipse(const Point& leftTop, double width, double height) override;

private:
	Color m_color;
	double m_lineWidth;
	svg::Document m_doc;
};

CSvgCanvas::CSvgCanvas(const std::string& fileName, double width, double height, double lineWidth)
	: m_doc(fileName, svg::Layout(svg::Dimensions(width, height), svg::Layout::TopLeft))
	, m_lineWidth(lineWidth)
{
}

CSvgCanvas::~CSvgCanvas()
{
	m_doc.save();
}

void CSvgCanvas::SetColor(Color color)
{
	m_color = color;
}

svg::Color CanvasColorToSvgColor(Color color)
{
	switch (color)
	{
	case Green:
		return svg::Color::Green;
	case Red:
		return svg::Color::Red;
	case Blue:
		return svg::Color::Blue;
	case Yellow:
		return svg::Color::Yellow;
	case Pink:
		return svg::Color(255, 105, 180);
	case Black:
		return svg::Color::Black;
	default:
		return svg::Color::Transparent;
	}
}

void CSvgCanvas::DrawLine(const Point& from, const Point& to)
{
	svg::Polyline line(svg::Stroke(m_lineWidth, CanvasColorToSvgColor(m_color)));
	line << svg::Point(from.first, from.second) << svg::Point(to.first, to.second);

	m_doc << line;
}

void CSvgCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	double centerX = leftTop.first + width / 2;
	double centerY = leftTop.second + height / 2;
	svg::Elipse elipse(svg::Point(centerX, centerY), width, height, svg::Fill(), svg::Stroke(m_lineWidth, CanvasColorToSvgColor(m_color)));

	m_doc << elipse;
}