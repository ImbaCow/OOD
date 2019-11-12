#pragma once
#include "CShape.h"

class CEllipseShape : public CShape
{
public:
	CEllipseShape(const Rect& frame, std::shared_ptr<IStyle> fillStyle, std::shared_ptr<ILineStyle> lineStyle);

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
