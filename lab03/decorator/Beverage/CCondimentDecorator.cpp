#include "pch.h"
#include "CCondimentDecorator.h"

std::string CCondimentDecorator::GetDescription() const
{
	return m_beverage->GetDescription() + GetCondimentDescription();
}

double CCondimentDecorator::GetCost() const
{
	return m_beverage->GetCost() + GetCondimentCost();
}

CCondimentDecorator::CCondimentDecorator(IBeveragePtr&& beverage)
	: m_beverage(move(beverage))
{
}
