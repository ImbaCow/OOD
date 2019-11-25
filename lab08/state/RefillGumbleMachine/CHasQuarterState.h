#pragma once
#include "pch.h"
#include "IRefilIState.h"
#include "IRefillGumballMachine.h"

class CHasQuarterState : public IRefilIState
{
public:
	const size_t MAX_QUARTERS_COUNT = 5u;

	CHasQuarterState(IRefillGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		m_gumballMachine.AddQuarter();
		std::cout << "You inserted another quarter\n";
		if (m_gumballMachine.GetQuarterCount() >= MAX_QUARTERS_COUNT)
		{
			m_gumballMachine.SetMaxQuarterCountState();
		}
	}

	void EjectQuarter() override
	{
		m_gumballMachine.EjectQuarters();
		m_gumballMachine.SetNoQuarterState();
	}

	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SetSoldState();
	}

	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}

	std::string ToString() const override
	{
		return "waiting for turn of crank or insert of quarter";
	}

	void Refill(size_t ballsCount) override
	{
		m_gumballMachine.AddBalls(ballsCount);
	}
private:
	IRefillGumballMachine& m_gumballMachine;
};

