#pragma once
#include <boost/format.hpp>
#include <iostream>

namespace modern_graphics_lib
{
using namespace std;

class CPoint
{
public:
	CPoint(int x, int y)
		: x(x)
		, y(y)
	{
	}

	int x;
	int y;
};

// ���� � ������� RGBA, ������ ��������� ��������� �������� �� 0.0f �� 1.0f
class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{
	}
	float r, g, b, a;
};

// ����� ��� ������������ ��������� �������
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(ostream& strm)
		: m_out(strm)
	{
	}

	~CModernGraphicsRenderer()
	{
		if (m_drawing) // ��������� ���������, ���� ��� ���� ������
		{
			EndDraw();
		}
	}

	// ���� ����� ������ ���� ������ � ������ ���������
	void BeginDraw()
	{
		if (m_drawing)
		{
			throw logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << endl;
		m_drawing = true;
	}

	// ��������� ��������� �����
	void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
	{
		// TODO: ������� � output ���������� ��� ��������� ����� � ����
		// <line fromX="3" fromY="5" toX="5" toY="17">
		//   <color r="0.35" g="0.47" b="1.0" a="1.0" />
		// </line>
		// ����� �������� ������ ����� BeginDraw() � EndDraw()
		if (!m_drawing)
		{
			throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">
    <color r="%5%" g="%6%" b="%7%" a="%8%" />
  </line>)") % start.x
				% start.y % end.x % end.y % color.r % color.g % color.b % color.a
			  << endl;
	}

	// ���� ����� ������ ���� ������ � ����� ���������
	void EndDraw()
	{
		if (!m_drawing)
		{
			throw logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << endl;
		m_drawing = false;
	}

private:
	ostream& m_out;
	bool m_drawing = false;
};
} // namespace modern_graphics_lib
