#pragma once
#include "CShape.h"

class CRectangleShape : public CShape
{
public:
	CRectangleShape(const Point& leftTop, double width, double height);
	virtual ~CRectangleShape() = default;

	virtual void Draw(const ICanvas& canvas) override;

protected:
	virtual void ResizeShape(const Rect& newRect) override;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
};
