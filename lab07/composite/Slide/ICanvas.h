#pragma once
#include "CommonTypes.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void SetLineSize(double lineSize) = 0;
	virtual void SetFillColor(RGBAColor color) = 0;
	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(const Point& leftTop, double width, double height) = 0;
	virtual void FillPolygon(const std::vector<Point>& pointsArr) = 0;
	virtual void FillEllipse(const Point& leftTop, double width, double height) = 0;
};