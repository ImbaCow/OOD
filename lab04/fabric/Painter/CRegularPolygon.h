#pragma once
#include "CShape.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, size_t vertexCount, const Point& center, double radius);
	virtual ~CRegularPolygon() = default;

	virtual void Draw(ICanvas& canvas) const override;

	size_t GetVertexCount() const;
	Point GetCenter() const;
	double GetRadius() const;

private:
	size_t m_vertexCount;
	Point m_center;
	double m_radius;

	Point GetVertexByIndex(size_t index) const;
};
