#include "pch.h"
#include "CChocolate.h"

CChocolate::CChocolate(IBeveragePtr&& beverage, size_t quantity)
	: CCondimentDecorator(move(beverage))
	, m_quantity(std::min(quantity, MAX_SLICES_COUNT))
{
}

double CChocolate::GetCondimentCost() const
{
	return static_cast<double>(10 * m_quantity);
}

std::string CChocolate::GetCondimentDescription() const
{
	return "Chocolate x " + std::to_string(m_quantity);
}
