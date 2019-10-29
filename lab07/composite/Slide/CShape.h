#pragma once
#include "CLineStyle.h"
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape(const Rect& rect);
	~CShape() = default;

	virtual Rect GetFrame() override;
	virtual void SetFrame(const Rect& rect) override;

	virtual ILineStyle& GetOutlineStyle() override;
	virtual const ILineStyle& GetOutlineStyle() const override;

	virtual IStyle& GetFillStyle() override;
	virtual const IStyle& GetFillStyle() const override;

protected:
	virtual void ResizeShape(const Rect& newRect) = 0;

private:
	Rect m_frame;
	CLineStyle m_lineStyle;
	CStyle m_fillStyle;
};
