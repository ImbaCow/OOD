#include "pch.h"
#include "CSyrup.h"

CSyrup::CSyrup(IBeveragePtr&& beverage, SyrupType syrupType)
	: CCondimentDecorator(move(beverage))
	, m_syrupType(syrupType)
{
}

double CSyrup::GetCondimentCost() const
{
	return 15;
}

std::string CSyrup::GetCondimentDescription() const
{
	return std::string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple")
		+ " syrup, ";
}
