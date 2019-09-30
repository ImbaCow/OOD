#pragma once
#include "pch.h"
#include "CCondimentDecorator.h"

enum class LiquorType
{
	Nuts,
	Chocolate
};

class ÑLiquor : public CCondimentDecorator
{
public:
	ÑLiquor(IBeveragePtr&& beverage, LiquorType type = LiquorType::Chocolate);

protected:
	double GetCondimentCost() const override;
	std::string GetCondimentDescription() const override;

private:
	LiquorType m_type;
};
