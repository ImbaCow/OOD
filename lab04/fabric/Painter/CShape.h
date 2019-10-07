#pragma once
#include "pch.h"
#include "ICanvas.h"

class CShape
{
public:
	CShape(Color color);
	virtual ~CShape() = default;

	virtual void Draw(std::shared_ptr<ICanvas>& canvas) const = 0;
	Color GetColor() const;

private:
	Color m_color;
};
