#include "pch.h"
#include "CLemon.h"

CLemon::CLemon(IBeveragePtr&& beverage, unsigned quantity)
	: CCondimentDecorator(move(beverage))
	, m_quantity(quantity)
{
}

double CLemon::GetCondimentCost() const
{
	return 10 * m_quantity;
}

std::string CLemon::GetCondimentDescription() const
{
	return "Lemon x " + std::to_string(m_quantity) + ", ";
}
