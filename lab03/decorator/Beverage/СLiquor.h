#pragma once
#include "pch.h"
#include "CCondimentDecorator.h"

enum class LiquorType
{
	Nuts,
	Chocolate
};

class �Liquor : public CCondimentDecorator
{
public:
	�Liquor(IBeveragePtr&& beverage, LiquorType type = LiquorType::Chocolate);

protected:
	double GetCondimentCost() const override;
	std::string GetCondimentDescription() const override;

private:
	LiquorType m_type;
};
