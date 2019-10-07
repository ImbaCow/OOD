#pragma once
#include "pch.h"
#include "CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, const Point& leftTop, const Point& rightBottom);
	virtual ~CRectangle() = default;

	virtual void Draw(std::shared_ptr<ICanvas>& canvas) const override;
	Point GetLeftTop() const;
	Point GetRightBottom() const;

private:
	Point m_leftTop;
	Point m_rightBottom;
};
