#include "pch.h"
#include "CModernCanvasAdapter.h"

const modern_graphics_lib::CPoint BASE_POINT(0, 0);
const modern_graphics_lib::CRGBAColor BASE_COLOR(0, 0, 0, 1);

CModernCanvasAdapter::CModernCanvasAdapter(std::ostream& out)
	: CModernGraphicsRenderer(out)
	, m_point(BASE_POINT)
	, m_color(BASE_COLOR)
{
	BeginDraw();
}

void CModernCanvasAdapter::MoveTo(int x, int y)
{
	m_point = { x, y };
}

void CModernCanvasAdapter::LineTo(int x, int y)
{
	DrawLine(m_point, { x, y }, m_color);
	MoveTo(x, y);
}

float GetDoubleFromHex(uint32_t hexValue, uint32_t mask)
{
	return static_cast<float>(hexValue & mask) / static_cast<float>(mask);
}

void CModernCanvasAdapter::SetColor(uint32_t rgbColor)
{
	m_color.r = GetDoubleFromHex(rgbColor, 0xFF000000);
	m_color.g = GetDoubleFromHex(rgbColor, 0x00FF0000);
	m_color.b = GetDoubleFromHex(rgbColor, 0x0000FF00);
	m_color.a = GetDoubleFromHex(rgbColor, 0x000000FF);
}
