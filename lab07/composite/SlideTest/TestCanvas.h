#pragma once
#include "ICanvas.h"

class TestCanvas : public ICanvas
{
public:
	TestCanvas(std::ostream& out);

	virtual void SetLineColor(RGBAColor color) override;
	virtual void SetLineSize(double lineSize) override;
	virtual void SetFillColor(RGBAColor color) override;

	virtual void DrawLine(const Point& from, const Point& to) override;
	virtual void DrawEllipse(const Point& leftTop, double width, double height) override;

	virtual void FillPolygon(const std::vector<Point>& pointsArr) override;
	virtual void FillEllipse(const Point& leftTop, double width, double height) override;

private:
	std::ostream& m_out;
};
