#pragma once
#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(Color color, const Point& leftTop, double width, double height);
	virtual ~CEllipse() = default;

	virtual void Draw(ICanvas& canvas) const override;
	Point GetLeftTop() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
};
