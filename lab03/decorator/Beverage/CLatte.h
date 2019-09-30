#pragma once
#include "pch.h"
#include "CCoffee.h"

class CLatte : public CCoffee
{
public:
	CLatte();

	double GetCost() const override;
};

