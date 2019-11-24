#pragma once
#include "CLineStyle.h"
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape(const Rect& rect, std::unique_ptr<IStyle> fillStyle, std::unique_ptr<ILineStyle> lineStyle);
	~CShape() = default;

	virtual std::optional<Rect> GetFrame() override;
	virtual void SetFrame(const Rect& rect) override;

	virtual const std::shared_ptr<ILineStyle> GetOutlineStyle() override;
	virtual const std::shared_ptr<const ILineStyle> GetOutlineStyle() const override;

	virtual const std::shared_ptr<IStyle> GetFillStyle() override;
	virtual const std::shared_ptr<const IStyle> GetFillStyle() const override;

	virtual void Draw(ICanvas& canvas) override;

protected:
	virtual void ResizeShape(const Rect& newRect) = 0;
	virtual void DrawColoredLine(ICanvas& canvas) = 0;
	virtual void DrawColoredFill(ICanvas& canvas) = 0;

private:
	Rect m_frame;
	const std::shared_ptr<ILineStyle> m_lineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};
