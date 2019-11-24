#pragma once
#include "pch.h"
#include "IMultiGumballMachine.h"

struct IRefillGumballMachine : public IMultiGumballMachine
{
	virtual void AddBalls(size_t ballsCount) = 0;

	~IRefillGumballMachine() = default;
};