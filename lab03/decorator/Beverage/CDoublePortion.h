#pragma once
#include "CCondimentDecorator.h"

class CDoublePortion : public CCondimentDecorator
{
public:
	CDoublePortion(IBeveragePtr&& beverage, double addCost);
	virtual ~CDoublePortion() = default;

	virtual std::string GetCondimentDescription() const override;
	virtual double GetCondimentCost() const override;

private:
	double m_addCost;
};
