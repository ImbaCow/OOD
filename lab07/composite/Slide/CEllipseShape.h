#pragma once
#include "CShape.h"

class CEllipseShape : public CShape
{
public:
	CEllipseShape(const Point& leftTop, double width, double height);

	virtual void Draw(const ICanvas& canvas) override;

protected:
	virtual void ResizeShape(const Rect& newRect) override;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
};
