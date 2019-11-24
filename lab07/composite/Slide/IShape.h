#pragma once
#include "IDrawable.h"
#include "IStyle.h"
#include "ILineStyle.h"

class IShape : public IDrawable
{
public:
	virtual std::optional<Rect> GetFrame() = 0;
	virtual void SetFrame(const Rect & rect) = 0;

	virtual const std::shared_ptr<ILineStyle> GetOutlineStyle() = 0;
	virtual const std::shared_ptr<const ILineStyle> GetOutlineStyle() const = 0;

	virtual const std::shared_ptr<IStyle> GetFillStyle() = 0;
	virtual const std::shared_ptr<const IStyle> GetFillStyle() const = 0;

	virtual ~IShape() = default;
};