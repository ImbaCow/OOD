#pragma once
#include "CShape.h"
#include "CStyleGroup.h"
#include "CLineStyleGroup.h"

class CShapeGroup : public IShape
{
public:
	CShapeGroup(const std::vector<std::shared_ptr<IShape>>& shapes);

	virtual void Draw(ICanvas& canvas) override;

	virtual std::optional<Rect> GetFrame() override;
	virtual void SetFrame(const Rect& rect) override;

	virtual const std::shared_ptr<ILineStyle> GetOutlineStyle() override;
	virtual const std::shared_ptr<const ILineStyle> GetOutlineStyle() const override;

	virtual const std::shared_ptr<IStyle> GetFillStyle() override;
	virtual const std::shared_ptr<const IStyle> GetFillStyle() const override;

private:
	std::optional<Rect> m_frame;
	std::vector<std::shared_ptr<IShape>> m_shapes;
	const std::shared_ptr<IStyle>  m_fillStyle;
	const std::shared_ptr<ILineStyle> m_lineStyle;
};
