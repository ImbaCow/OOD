#pragma once
#include "pch.h"
#include "IRefilIState.h"
#include "IRefillGumballMachine.h"

class CNoQuarterState : public IRefilIState
{
public:
	CNoQuarterState(IRefillGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		m_gumballMachine.AddQuarter();
		std::cout << "You inserted a quarter\n";
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}

	void Refill(size_t ballsCount) override
	{
		m_gumballMachine.AddBalls(ballsCount);
	}

private:
	IRefillGumballMachine& m_gumballMachine;
};

