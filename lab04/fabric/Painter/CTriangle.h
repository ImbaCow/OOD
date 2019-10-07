#pragma once
#include "pch.h"
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(Color color, const Point& vertex1, const Point& vertex2, const Point& vertex3);
	virtual ~CTriangle() = default;

	virtual void Draw(std::shared_ptr<ICanvas>& canvas) const override;

	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
