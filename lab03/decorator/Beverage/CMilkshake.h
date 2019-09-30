#pragma once
#include "pch.h"
#include "CBeverage.h"

enum MilkshakeType
{
	Small,
	Medium,
	Large
};

class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeType type = MilkshakeType::Medium);

	double GetCost() const;

private:
	MilkshakeType m_type;
};
