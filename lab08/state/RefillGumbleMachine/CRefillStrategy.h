#pragma once
#include "pch.h"
#include "IRefillStrategy.h"
#include "IRefillGumballMachine.h"

class CRefillStrategy : public IRefillStrategy
{
	CRefillStrategy(IRefillGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{
	}

	virtual void AddBalls(size_t ballsCount) override
	{
		m_gumballMachine.AddBalls(ballsCount);
	}

private:
	IRefillGumballMachine& m_gumballMachine;
};