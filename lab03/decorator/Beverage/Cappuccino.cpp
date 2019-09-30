#include "pch.h"
#include "Cappuccino.h"

CCappuccino::CCappuccino()
	: CCoffee("Cappuccino")
{
}

double CCappuccino::GetCost() const
{
	return 80;
}
