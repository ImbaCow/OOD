#pragma once
#include "CShape.h"

class CTriangleShape : public CShape
{
public:
	CTriangleShape(const Point& vertex1, const Point& vertex2, const Point& vertex3);

	virtual void Draw(const ICanvas& canvas) override;

protected:
	virtual void ResizeShape(const Rect& newRect) override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
