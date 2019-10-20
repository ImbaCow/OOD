#pragma once
#include "pch.h"

class CModernCanvasAdapter : public graphics_lib::ICanvas
{
public:
	CModernCanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer);
	virtual ~CModernCanvasAdapter() = default;

	virtual void MoveTo(int x, int y) override;
	virtual void LineTo(int x, int y) override;
	virtual void SetColor(uint32_t rgbColor) override;

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CPoint m_point;
	modern_graphics_lib::CRGBAColor m_color;
};
