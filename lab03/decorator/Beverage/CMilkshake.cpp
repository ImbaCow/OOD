#include "pch.h"
#include "CMilkshake.h"

CMilkshake::CMilkshake(MilkshakeType type)
	: CBeverage("Milkshake")
	, m_type(type)
{
}

double CMilkshake::GetCost() const
{
	switch (m_type)
	{
	case Small:
		return 50.0;
	case Large:
		return 80.0;
	default:
		return 60.0;
	}
}
