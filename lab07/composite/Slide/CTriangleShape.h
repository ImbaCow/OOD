#pragma once
#include "CShape.h"

class CTriangleShape : public CShape
{
public:
	CTriangleShape(const Point& vertex1, const Point& vertex2, const Point& vertex3, std::unique_ptr<IStyle> fillStyle, std::unique_ptr<ILineStyle> lineStyle);

	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

protected:
	virtual void ResizeShape(const Rect& newRect) override;
	virtual void DrawColoredLine(ICanvas& canvas) override;
	virtual void DrawColoredFill(ICanvas& canvas) override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
