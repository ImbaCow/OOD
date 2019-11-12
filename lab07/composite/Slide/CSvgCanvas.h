#pragma once
#include "ICanvas.h"
#include "simple_svg_1.0.0.hpp"

class CSvgCanvas : public ICanvas
{
public:
	CSvgCanvas(std::shared_ptr<svg::Document> doc);
	~CSvgCanvas() = default;

	virtual void SetLineColor(RGBAColor color) override;
	virtual void SetLineSize(double lineSize) override;
	virtual void SetFillColor(RGBAColor color) override;

	virtual void DrawLine(const Point& from, const Point& to) override;
	virtual void DrawEllipse(const Point& leftTop, double width, double height) override;

	virtual void FillPolygon(const std::vector<Point>& pointsArr) override;
	virtual void FillEllipse(const Point& leftTop, double width, double height) override;

private:
	svg::Color m_lineColor = svg::Color::Transparent;
	svg::Color m_fillColor = svg::Color::Transparent;
	double m_lineSize = 0;
	std::shared_ptr<svg::Document> m_doc;
};

svg::Color CanvasColorToSvgColor(RGBAColor color)
{
	uint8_t r = (color >> 24) % 256;
	uint8_t g = (color >> 16) % 256;
	uint8_t b = (color >> 8) % 256;
	double a = static_cast<double>(color % 256) / 256;

	return svg::Color(r, g, b, a);
}

CSvgCanvas::CSvgCanvas(std::shared_ptr<svg::Document> doc)
	: m_doc(doc)
{
}

void CSvgCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = CanvasColorToSvgColor(color);
}

void CSvgCanvas::SetLineSize(double lineSize)
{
	m_lineSize = lineSize;
}

void CSvgCanvas::SetFillColor(RGBAColor color)
{
	m_fillColor = CanvasColorToSvgColor(color);
}

void CSvgCanvas::DrawLine(const Point& from, const Point& to)
{
	svg::Polyline line(svg::Stroke(m_lineSize, m_lineColor));
	line << svg::Point(from.x, from.y) << svg::Point(to.x, to.y);

	*m_doc << line;
}

void CSvgCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	double centerX = leftTop.x + width / 2;
	double centerY = leftTop.y + height / 2;
	svg::Elipse elipse(svg::Point(centerX, centerY), width, height, svg::Fill(), svg::Stroke(m_lineSize, m_lineColor));

	*m_doc << elipse;
}

void CSvgCanvas::FillPolygon(const std::vector<Point>& pointsArr)
{
	svg::Polygon polygon(m_fillColor);
	for (const auto& point : pointsArr)
	{
		svg::Point svgPoint{ point.x, point.y };
		polygon << svgPoint;
	}

	*m_doc << polygon;
}

void CSvgCanvas::FillEllipse(const Point& leftTop, double width, double height)
{
	double centerX = leftTop.x + width / 2;
	double centerY = leftTop.y + height / 2;
	svg::Elipse elipse(svg::Point(centerX, centerY), width, height, svg::Fill(m_fillColor));

	*m_doc << elipse;
}
