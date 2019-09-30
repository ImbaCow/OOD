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
	�Liquor(IBeveragePtr&& beverage, LiquorType type = LiquorType::Chocolate)
		: CCondimentDecorator(move(beverage))
		, m_type(type)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 50;
	}

	std::string GetCondimentDescription() const override
	{
		return std::string(m_type == LiquorType::Nuts ? "Nuts" : "Chocolate")
			+ " liquor";
	}

private:
	LiquorType m_type;
};
