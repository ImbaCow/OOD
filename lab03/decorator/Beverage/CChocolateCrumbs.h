#pragma once
#include "pch.h"
#include "CCondimentDecorator.h"

class CChocolateCrumbs : public CCondimentDecorator
{
public:
	CChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass);

	double GetCondimentCost() const override;
	std::string GetCondimentDescription() const override;

private:
	unsigned m_mass;
};
