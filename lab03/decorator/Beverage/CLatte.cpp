#include "pch.h"
#include "CLatte.h"

CLatte::CLatte()
	: CCoffee("Latte")
{
}

double CLatte::GetCost() const
{
	return 90;
}
