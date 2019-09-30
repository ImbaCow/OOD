#pragma once
#include "pch.h"
#include "CCondimentDecorator.h"

class CCream : public CCondimentDecorator
{
public:
	CCream(IBeveragePtr&& beverage);

protected:
	double GetCondimentCost() const override;
	std::string GetCondimentDescription() const override;
};