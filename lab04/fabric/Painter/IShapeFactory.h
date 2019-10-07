#pragma once
#include "pch.h"
#include "CShape.h"

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;

	virtual std::shared_ptr<CShape> CreateShape(const std::string& description) = 0;
};
