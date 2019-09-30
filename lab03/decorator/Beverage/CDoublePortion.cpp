#include "pch.h"
#include "CDoublePortion.h"

CDoublePortion::CDoublePortion(IBeveragePtr&& beverage, double addCost = 40)
	: CCondimentDecorator(move(beverage))
	, m_addCost(addCost)
{
}

std::string CDoublePortion::GetCondimentDescription() const
{
	return "2x of ";
}

double CDoublePortion::GetCondimentCost() const
{
	return m_addCost;
}
