#pragma once
#include "pch.h"
#include "CCondimentDecorator.h"

class CChocolate : public CCondimentDecorator
{
public:
	CChocolate(IBeveragePtr&& beverage, size_t quantity = 1)
		: CCondimentDecorator(move(beverage))
		, m_quantity(std::min(quantity, MAX_SLICES_COUNT))
	{
	}

	static const size_t MAX_SLICES_COUNT = 5;

protected:
	double GetCondimentCost() const override
	{
		return 10 * m_quantity;
	}
	std::string GetCondimentDescription() const override
	{
		return "Chocolate x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
};