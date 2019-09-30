#pragma once
#include "pch.h"
#include "CBeverage.h"

class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea");

	double GetCost() const override;
};

class CBlackTea : public CTea
{
public:
	CBlackTea()
		: CTea("Black tea")
	{
	}
};

class CRedTea : public CTea
{
public:
	CRedTea()
		: CTea("Red tea")
	{
	}
};

class CGreenTea : public CTea
{
public:
	CGreenTea()
		: CTea("Green tea")
	{
	}
};

class COrangeTea : public CTea
{
public:
	COrangeTea()
		: CTea("Orange tea")
	{
	}
};