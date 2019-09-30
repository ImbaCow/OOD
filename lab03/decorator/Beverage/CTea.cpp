#include "pch.h"
#include "CTea.h"

CTea::CTea(const std::string& description)
	: CBeverage(description)
{
}

double CTea::GetCost() const
{
	return 30;
}
