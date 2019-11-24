#pragma once
#include "CShape.h"

class CRectangleShape : public CShape
{
public:
	CRectangleShape(const Rect& rectangleFrame, std::unique_ptr<IStyle> fillStyle, std::unique_ptr<ILineStyle> lineStyle);
	virtual ~CRectangleShape() = default;

	Point GetLeftTop();
	double GetWidth();
	double GetHeight();

protected:
	virtual void ResizeShape(const Rect& newRect) override;
	virtual void DrawColoredLine(ICanvas& canvas) override;
	virtual void DrawColoredFill(ICanvas& canvas) override;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
};
