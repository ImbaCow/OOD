#include "pch.h"
#include "CChocolateCrumbs.h"

CChocolateCrumbs::CChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass)
	: CCondimentDecorator(move(beverage))
	, m_mass(mass)
{
}

double CChocolateCrumbs::GetCondimentCost() const
{
	return 2 * m_mass;
}

std::string CChocolateCrumbs::GetCondimentDescription() const
{
	return "Chocolate crumbs " + std::to_string(m_mass) + "g, ";
}
