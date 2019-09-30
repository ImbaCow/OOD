#pragma once
#include "pch.h"
#include "CCoffee.h"

class CCappuccino : public CCoffee
{
public:
	CCappuccino();

	double GetCost() const override;
};