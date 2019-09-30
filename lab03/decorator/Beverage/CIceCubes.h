#pragma once
#include "pch.h"
#include "CCondimentDecorator.h"

enum class IceCubeType
{
	Dry,
	Water
};

class CIceCubes : public CCondimentDecorator
{
public:
	CIceCubes(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type = IceCubeType::Water);

protected:
	double GetCondimentCost() const override;
	std::string GetCondimentDescription() const override;

private:
	unsigned m_quantity;
	IceCubeType m_type;
};
