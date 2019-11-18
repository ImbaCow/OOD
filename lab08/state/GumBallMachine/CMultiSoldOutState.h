#pragma once
#include "pch.h"
#include "IState.h"
#include "IMultiGumballMachine.h"

class CMultiSoldOutState : public IState
{
public:
	CMultiSoldOutState(IMultiGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		if (size_t quarterCount = m_gumballMachine.GetQuarterCount(); quarterCount)
		{
			for (size_t i = 0; i < quarterCount; ++i)
			{
				m_gumballMachine.ReleaseQuarter();
			}
			std::cout << "All quarters returned\n";
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
private:
	IMultiGumballMachine& m_gumballMachine;
};
