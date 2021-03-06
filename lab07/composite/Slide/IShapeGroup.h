#pragma once
#include "IShape.h"

class IShapeGroup : public IShape
{
public:
	virtual void AddShape(std::shared_ptr<IShape> shape) = 0;
	virtual void RemoveShape(size_t index) = 0;
	
	virtual std::shared_ptr<IShape> GetShape(size_t index) const = 0;
	virtual size_t GetShapesCount() const = 0;

	virtual ~IShapeGroup() = default;
};