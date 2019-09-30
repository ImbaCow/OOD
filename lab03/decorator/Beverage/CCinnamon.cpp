#include "pch.h"
#include "CCinnamon.h"

CCinnamon::CCinnamon(IBeveragePtr&& beverage)
	: CCondimentDecorator(move(beverage))
{
}

double CCinnamon::GetCondimentCost() const
{
	return 20;
}

std::string CCinnamon::GetCondimentDescription() const
{
	return "Cinnamon, ";
}
