#include "pch.h"
#include "CCream.h"

CCream::CCream(IBeveragePtr&& beverage)
	: CCondimentDecorator(move(beverage))
{
}

double CCream::GetCondimentCost() const
{
	return 25;
}

std::string CCream::GetCondimentDescription() const
{
	return "Cream";
}
