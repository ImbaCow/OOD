#pragma once
#include "CShape.h"

class CShapeGroup : public CShape
{
public:
	CShapeGroup(const std::vector<std::shared_ptr<IShape>>& shapes);

	virtual void Draw(const ICanvas& canvas) override;

protected:
	virtual void ResizeShape(const Rect& newRect) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
