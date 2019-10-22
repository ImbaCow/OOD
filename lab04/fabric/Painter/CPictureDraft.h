#pragma once
#include "CShape.h"

class CPictureDraft
{
public:
	CPictureDraft(const std::vector<std::shared_ptr<CShape>>& shapeArr);

	size_t GetShapeCount() const;
	std::shared_ptr<CShape> GetShape(size_t index) const;

private:
	std::vector<std::shared_ptr<CShape>> m_shapeArr;
};
