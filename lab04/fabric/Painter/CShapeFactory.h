#pragma once
#include "IShapeFactory.h"
#include "CEllipse.h"
#include "CRectangle.h"
#include "CRegularPolygon.h"
#include "CTriangle.h"

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	virtual ~CShapeFactory() = default;

	virtual std::shared_ptr<CShape> CreateShape(const std::string& description) override;

private:
	std::map<std::string, std::function<std::shared_ptr<CShape>(std::istream&)>> m_shapeGeneratorsMap;
};
