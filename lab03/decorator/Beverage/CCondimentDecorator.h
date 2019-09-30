#pragma once
#include "pch.h"
#include "IBeverage.h"

class CCondimentDecorator : public IBeverage
{
public:
	std::string GetDescription() const override;

	double GetCost() const override;

	virtual std::string GetCondimentDescription()const = 0;
	virtual double GetCondimentCost()const = 0;
protected:
	CCondimentDecorator(IBeveragePtr&& beverage);

private:
	IBeveragePtr m_beverage;
};
