#pragma once
#include "IDrawable.h"
#include "IStyle.h"
#include "ILineStyle.h"

class IShape : public IDrawable
{
public:
	virtual Rect GetFrame() = 0;
	virtual void SetFrame(const Rect & rect) = 0;

	virtual ILineStyle& GetOutlineStyle() = 0;
	virtual const ILineStyle& GetOutlineStyle() const = 0;

	virtual IStyle & GetFillStyle() = 0;
	virtual const IStyle & GetFillStyle()const = 0;

	virtual ~IShape() = default;
};