#pragma once
#include <ICanvas.h>

struct EllipseTest
{
	Point leftTop;
	double width;
	double height;
};

class TestCanvas : public ICanvas
{
public:
	virtual ~TestCanvas() = default;

	virtual void SetColor(Color color) override;
	virtual void DrawLine(const Point& from, const Point& to) override;
	virtual void DrawEllipse(const Point& leftTop, double width, double height) override;

	std::vector<std::pair<Point, Point>> m_lineArr;
	std::vector<EllipseTest> m_ellipseArr;
	Color m_color;
};
