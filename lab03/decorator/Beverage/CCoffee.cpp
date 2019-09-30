#include "pch.h"
#include "CCoffee.h"

CCoffee::CCoffee(const std::string& description)
	: CBeverage(description)
{
}

double CCoffee::GetCost() const
{
	return 60;
}
