#include "pch.h"
#include "CShape.h"

CShape::CShape(const Rect& rect, std::unique_ptr<IStyle> fillStyle, std::unique_ptr<ILineStyle> lineStyle)
	: m_frame(rect)
	, m_fillStyle(move(fillStyle))
	, m_lineStyle(move(lineStyle))
{
	if (!(m_fillStyle && m_lineStyle))
	{
		throw std::invalid_argument("Style cannot be nullptr");
	}
}

std::optional<Rect> CShape::GetFrame()
{
	return m_frame;
}

void CShape::SetFrame(const Rect& rect)
{
	ResizeShape(rect);
	m_frame = rect;
}

const std::shared_ptr<ILineStyle> CShape::GetOutlineStyle()
{
	return m_lineStyle;
}

const std::shared_ptr<const ILineStyle> CShape::GetOutlineStyle() const
{
	return m_lineStyle;
}

const std::shared_ptr<IStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

const std::shared_ptr<const IStyle> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

void CShape::Draw(ICanvas& canvas)
{
	if (auto isEnebledOpt = m_fillStyle->IsEnabled(); isEnebledOpt.has_value() && isEnebledOpt.value())
	{
		auto fillStyleColor = m_fillStyle->GetColor();
		canvas.SetFillColor(fillStyleColor.has_value() ? fillStyleColor.value() : 0u);
		DrawColoredFill(canvas);
	}

	if (auto isEnebledOpt = m_lineStyle->IsEnabled(); isEnebledOpt.has_value() && isEnebledOpt.value())
	{
		auto lineStyleColor = m_lineStyle->GetColor();
		auto lineStyleSize = m_lineStyle->GetLineSize();
		canvas.SetLineColor(lineStyleColor.has_value() ? lineStyleColor.value() : 0u);
		canvas.SetLineSize(lineStyleSize.has_value() ? lineStyleSize.value() : 0.0);
		DrawColoredLine(canvas);
	}
}

const std::shared_ptr<IShapeGroup> CShape::TryGetGroup()
{
	return nullptr;
}
