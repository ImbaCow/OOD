#include "pch.h"
#include "ÑLiquor.h"

ÑLiquor::ÑLiquor(IBeveragePtr&& beverage, LiquorType type)
	: CCondimentDecorator(move(beverage))
	, m_type(type)
{
}

double ÑLiquor::GetCondimentCost() const
{
	return 50;
}

std::string ÑLiquor::GetCondimentDescription() const
{
	return std::string(m_type == LiquorType::Nuts ? "Nuts" : "Chocolate")
		+ " liquor";
}
