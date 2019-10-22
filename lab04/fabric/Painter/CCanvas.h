#pragma once
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream& stream);
	virtual ~CCanvas() = default;

	virtual void SetColor(Color color) override;
	virtual void DrawLine(const Point& from, const Point& to) override;
	virtual void DrawEllipse(const Point& leftTop, double width, double height) override;

private:
	Color m_color;
	std::ostream& m_stream;
};
