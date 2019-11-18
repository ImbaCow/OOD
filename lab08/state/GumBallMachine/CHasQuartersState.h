#pragma once
#include "pch.h"
#include "IState.h"
#include "IMultiGumballMachine.h"

class CHasQuartersState : public IState
{
public:
	const size_t MAX_QUARTERS_COUNT = 5u;

	CHasQuartersState(IMultiGumballMachine& gumballMachine)
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
		for (size_t i = 0; i < m_gumballMachine.GetQuarterCount(); i++)
		{
			m_gumballMachine.ReleaseQuarter();
		}
		std::cout << "All quarters returned\n";
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
		return "waiting for turn of crank with " + std::to_string(m_gumballMachine.GetQuarterCount()) + " quarters";
	}
private:
	IMultiGumballMachine& m_gumballMachine;
};

