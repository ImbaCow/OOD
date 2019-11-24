#include "pch.h"
#include "CShapeGroup.h"

namespace
{
std::optional<Rect> CalcCompositeFrame(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	auto beginIt = shapes.begin();
	std::optional<Rect> resultRect = (*beginIt)->GetFrame();

	for (++beginIt; beginIt != shapes.end(); ++beginIt)
	{
		std::optional<Rect> frame = (*beginIt)->GetFrame();
		if (!resultRect)
		{
			resultRect = frame;
		}
		else if (frame)
		{
			resultRect.value().leftTop.x = std::min(resultRect.value().leftTop.x, frame.value().leftTop.x);
			resultRect.value().leftTop.y = std::min(resultRect.value().leftTop.y, frame.value().leftTop.y);

			resultRect.value().width = std::max(resultRect.value().width, frame.value().width);
			resultRect.value().height = std::max(resultRect.value().height, frame.value().height);
		}
	}

	return resultRect;
};

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

std::vector<std::shared_ptr<IStyle>> GetFillStyleArr(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	std::vector<std::shared_ptr<IStyle>> resultArr;
	std::for_each(shapes.begin(), shapes.end(), [&resultArr](const std::shared_ptr<IShape>& shapePtr) {
		resultArr.push_back(shapePtr->GetFillStyle());
	});

	return resultArr;
}

std::vector<std::shared_ptr<ILineStyle>> GetLineStyleArr(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	std::vector<std::shared_ptr<ILineStyle>> resultArr;
	std::for_each(shapes.begin(), shapes.end(), [&resultArr](const std::shared_ptr<IShape>& shapePtr) {
		resultArr.push_back(shapePtr->GetOutlineStyle());
	});

	return resultArr;
}
} // namespace

CShapeGroup::CShapeGroup(const std::vector<std::shared_ptr<IShape>>& shapes)
	: m_shapes(shapes)
	, m_frame(CalcCompositeFrame(shapes))
	, m_fillStyle(new CStyleGroup(GetFillStyleArr(shapes)))
	, m_lineStyle(new CLineStyleGroup(GetLineStyleArr(shapes)))
{
}

void CShapeGroup::Draw(ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

std::optional<Rect> CShapeGroup::GetFrame()
{
	return CalcCompositeFrame(m_shapes);
}

void CShapeGroup::SetFrame(const Rect& rect)
{
	std::optional<Rect> oldRect = GetFrame();
	for (auto& shape : m_shapes)
	{
		Rect newShapeRect = CalcChildFrame(oldRect, rect, shape->GetFrame());
		shape->SetFrame(newShapeRect);
	}
}

const std::shared_ptr<ILineStyle> CShapeGroup::GetOutlineStyle()
{
	return m_lineStyle;
}

const std::shared_ptr<const ILineStyle> CShapeGroup::GetOutlineStyle() const
{
	return m_lineStyle;
}

const std::shared_ptr<IStyle> CShapeGroup::GetFillStyle()
{
	return m_fillStyle;
}

const std::shared_ptr<const IStyle> CShapeGroup::GetFillStyle() const
{
	return m_fillStyle;
}
