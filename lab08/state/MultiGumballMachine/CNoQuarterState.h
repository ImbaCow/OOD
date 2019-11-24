#pragma once
#include "pch.h"
#include "IState.h"
#include "IMultiGumballMachine.h"

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IMultiGumballMachine& gumballMachine)
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
private:
	IMultiGumballMachine& m_gumballMachine;
};

