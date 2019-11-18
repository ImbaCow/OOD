#pragma once
#include "pch.h"
#include "CHasQuarterState.h"
#include "CNoQuarterState.h"
#include "CSoldOutState.h"
#include "CSoldState.h"

class CGumballMachine : private IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls)
		: m_count(numBalls)
	{

		if (m_count > 0)
		{
			SetNoQuarterState();
		}
		else
		{
			SetSoldOutState();
		}
	}

	void EjectQuarter()
	{
		m_currentState->EjectQuarter();
	}

	void InsertQuarter()
	{
		m_currentState->InsertQuarter();
	}

	void TurnCrank()
	{
		m_currentState->TurnCrank();
		m_currentState->Dispense();
	}

	std::string ToString()const
	{
		auto fmt = boost::format(R"(
Inventory: %1% gumball%2%
Machine is %3%
)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % m_currentState->ToString()).str();
	}
private:
	unsigned GetBallCount() const override
	{
		return m_count;
	}

	virtual void ReleaseBall() override
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}

	void SetSoldOutState() override
	{
		m_currentState.reset(new CSoldOutState(*this));
	}

	void SetNoQuarterState() override
	{
		m_currentState.reset(new CNoQuarterState(*this));
	}

	void SetSoldState() override
	{
		m_currentState.reset(new CSoldState(*this));
	}

	void SetHasQuarterState() override
	{
		m_currentState.reset(new CHasQuarterState(*this));
	}
private:
	unsigned m_count = 0;
	std::unique_ptr<IState> m_currentState;
};

