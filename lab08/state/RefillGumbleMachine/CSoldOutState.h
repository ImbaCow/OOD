#pragma once
#include "pch.h"
#include "IRefilIState.h"
#include "IRefillGumballMachine.h"

class CSoldOutState : public IRefilIState
{
public:
	CSoldOutState(IRefillGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		if (m_gumballMachine.GetQuarterCount())
		{
			m_gumballMachine.EjectQuarters();
		}
		else
		{
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
		}
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}

	void Refill(size_t ballsCount) override
	{
		m_gumballMachine.AddBalls(ballsCount);
		m_gumballMachine.SetHasQuarterState();
	}

private:
	IRefillGumballMachine& m_gumballMachine;
};
