#pragma once
#include "pch.h"
#include "IState.h"
#include "IMultiGumballMachine.h"

class CMaxQuarterCountState : public IState
{
public:
	CMaxQuarterCountState(IMultiGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		std::cout << "You can't insert another quarter\n";
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
		return "waiting for turn of crank with maximum quarters";
	}
private:
	IMultiGumballMachine& m_gumballMachine;
};

