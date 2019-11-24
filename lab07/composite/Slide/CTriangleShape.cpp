#include "pch.h"
#include "CTriangleShape.h"

namespace
{
Rect CalcTriangleFrame(const Point& vertex1, const Point& vertex2, const Point& vertex3)
{
	auto xMinMax = std::minmax({ vertex1.x, vertex2.x, vertex3.x });
	auto yMinMax = std::minmax({ vertex1.y, vertex2.y, vertex3.y });

	Point leftTop{ xMinMax.first, yMinMax.first };
	double width = xMinMax.second - xMinMax.first;
	double height = yMinMax.second - yMinMax.first;

	return {
		leftTop,
		width,
		height
	};
};
Point CalcVertex(const Point& oldVertex, const Rect& newRect, const Rect& oldRect)
{
	double widthRatio = oldRect.width ? newRect.width / oldRect.width : 0.0;
	double heightRatio = oldRect.height ? newRect.height / oldRect.height : 0.0;

	double vertexX = widthRatio * (oldVertex.x - oldRect.leftTop.x) + newRect.leftTop.x;
	double vertexY = heightRatio * (oldVertex.y - oldRect.leftTop.y) + newRect.leftTop.y;

	return {
		vertexX,
		vertexY
	};
};

} // namespace

CTriangleShape::CTriangleShape(const Point& vertex1, const Point& vertex2, const Point& vertex3, std::unique_ptr<IStyle> fillStyle, std::unique_ptr<ILineStyle> lineStyle)
	: CShape(CalcTriangleFrame(vertex1, vertex2, vertex3), move(fillStyle), move(lineStyle))
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

Point CTriangleShape::GetVertex1() const
{
	return m_vertex1;
}

Point CTriangleShape::GetVertex2() const
{
	return m_vertex2;
}

Point CTriangleShape::GetVertex3() const
{
	return m_vertex3;
}

void CTriangleShape::ResizeShape(const Rect& newRect)
{
	Rect oldRect = GetFrame();
	m_vertex1 = CalcVertex(m_vertex1, newRect, oldRect);
	m_vertex2 = CalcVertex(m_vertex2, newRect, oldRect);
	m_vertex3 = CalcVertex(m_vertex3, newRect, oldRect);
}

void CTriangleShape::DrawColoredLine(ICanvas& canvas)
{
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

void CTriangleShape::DrawColoredFill(ICanvas& canvas)
{
	canvas.FillPolygon({ m_vertex1,
		m_vertex2,
		m_vertex3 });
}
