#include "pch.h"
#include "TestCanvas.h"

TestCanvas::TestCanvas(std::ostream& out)
	: m_out(out)
{
	m_out.precision(1);
	m_out << std::fixed;
}

void TestCanvas::SetLineColor(RGBAColor color)
{
	m_out << "lineColor:" << color << std::endl;
}

void TestCanvas::SetLineSize(double lineSize)
{
	m_out << "lineSize:" << lineSize << std::endl;
}

void TestCanvas::SetFillColor(RGBAColor color)
{
	m_out << "fillColor:" << color << std::endl;
}

std::string PointToString(const Point& p)
{
	std::stringstream ss;
	ss.precision(1);
	ss << std::fixed << p.x << '/' << p.y;
	return ss.str();
}

void TestCanvas::DrawLine(const Point& from, const Point& to)
{
	m_out << "line:" << PointToString(from) << ';' << PointToString(to) << std::endl;
}

void TestCanvas::DrawEllipse(const Point& leftTop, double width, double height)
{
	m_out << "ellipse:" << PointToString(leftTop) << ';' << width << ';' << height << std::endl;
}

void TestCanvas::FillPolygon(const std::vector<Point>& pointsArr)
{
	m_out << "fillPolygon:";
	for (const auto& point : pointsArr)
	{
		m_out << PointToString(point) << ';';
	}
	m_out << std::endl;
}

void TestCanvas::FillEllipse(const Point& leftTop, double width, double height)
{
	m_out << "fillEllipse:" << PointToString(leftTop) << ';' << width << ';' << height << std::endl;
}
