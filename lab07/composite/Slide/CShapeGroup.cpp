#include "pch.h"
#include "CShapeGroup.h"

Rect CalcCompositeFrame(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	Point leftTop{};
	double width = 0;
	double height = 0;
	bool isFirst = true;

	for (const auto& shape : shapes)
	{
		Rect frame = shape->GetFrame();
		if (isFirst)
		{
			leftTop = frame.leftTop;
			width = frame.width;
			height = frame.height;
		}
		else
		{
			leftTop.x = std::min(leftTop.x, frame.leftTop.x);
			leftTop.y = std::min(leftTop.y, frame.leftTop.y);

			width = std::max(width, frame.width);
			height = std::max(height, frame.height);
		}
	}

	return {
		leftTop,
		width,
		height
	};
};

CShapeGroup::CShapeGroup(const std::vector<std::shared_ptr<IShape>>& shapes)
	: CShape(CalcCompositeFrame(shapes))
	, m_shapes(shapes)
{
}

void CShapeGroup::Draw(const ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

double CalcChildCoord(double newParentLen, double oldParentLen, double oldChildCoord, double oldParentCoord)
{
	if (oldParentLen)
	{
		return newParentLen / oldParentLen * (oldChildCoord - oldParentCoord);
	}
	return 0.0;
};

double CalcChildLen(double oldParentLen, double newParentLen, double oldChildLen)
{
	if (oldParentLen)
	{
		return newParentLen / oldParentLen * oldChildLen;
	}
	return newParentLen;
};

Rect CalcChildFrame(const Rect& oldParent, const Rect& newParent, const Rect& oldChild)
{
	double newChildX = CalcChildCoord(newParent.width, oldParent.width, oldChild.leftTop.x, oldParent.leftTop.x) + newParent.leftTop.x;
	double newChildY = CalcChildCoord(newParent.height, oldParent.height, oldChild.leftTop.y, oldParent.leftTop.y) + newParent.leftTop.y;

	double newChildWidth = CalcChildLen(oldParent.width, newParent.width, oldChild.width);
	double newChildHeight = CalcChildLen(oldParent.height, newParent.height, oldChild.height);

	return {
		{ newChildX,
			newChildY },
		newChildWidth,
		newChildHeight
	};
};

void CShapeGroup::ResizeShape(const Rect& newRect)
{
	for (auto& shape : m_shapes)
	{
		Rect newShapeRect = CalcChildFrame(GetFrame(), newRect, shape->GetFrame());
		shape->SetFrame(newShapeRect);
	}
}
