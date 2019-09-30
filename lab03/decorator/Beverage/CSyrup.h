#pragma once
#include "pch.h"
#include "CCondimentDecorator.h"

enum class SyrupType
{
	Chocolate,
	Maple,
};

class CSyrup : public CCondimentDecorator
{
public:
	CSyrup(IBeveragePtr&& beverage, SyrupType syrupType);

protected:
	double GetCondimentCost() const override;
	std::string GetCondimentDescription() const override;

private:
	SyrupType m_syrupType;
};

