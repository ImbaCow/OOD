#pragma once
#include "pch.h"
#include "CCondimentDecorator.h"

class CChocolate : public CCondimentDecorator
{
public:
	CChocolate(IBeveragePtr&& beverage, size_t quantity = 1);

	static const size_t MAX_SLICES_COUNT = 5;

protected:
	double GetCondimentCost() const override;
	std::string GetCondimentDescription() const override;

private:
	size_t m_quantity;
};