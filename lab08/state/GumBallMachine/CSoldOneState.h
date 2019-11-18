#include "pch.h"
#include "IState.h"
#include "IMultiGumballMachine.h"

class CSoldOneState : public IState
{
public:
	CSoldOneState(IMultiGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}
	void InsertQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void TurnCrank() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		m_gumballMachine.ReleaseQuarter();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else if (m_gumballMachine.GetQuarterCount())
		{
			m_gumballMachine.SetHasQuarterState();
		}
		else
		{
			m_gumballMachine.SetNoQuarterState();
		}
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}
private:
	IMultiGumballMachine& m_gumballMachine;
};