#pragma once
#include "pch.h"
#include "IShapeFactory.h"
#include "CEllipse.h"
#include "CRectangle.h"
#include "CRegularPolygon.h"
#include "CTriangle.h"

class CShapeFactory : public IShapeFactory
{
public:
	virtual ~CShapeFactory() = default;

	virtual std::shared_ptr<CShape> CreateShape(const std::string& description) override;
};
