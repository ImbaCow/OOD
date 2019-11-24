#pragma once
#include "pch.h"
#include "CMaxQuarterCountState.h"
#include "CHasQuarterState.h"
#include "CNoQuarterState.h"
#include "CSoldOutState.h"
#include "CSoldState.h"

class CMultiGumballMachine : private IMultiGumballMachine
{
public:
	CMultiGumballMachine(unsigned numBalls)
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
Inventory: %1% gumballs, %2% quarters 
Machine is %3%
)");
		return (fmt % m_count % m_quarterCount % m_currentState->ToString()).str();
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
		m_currentState.reset(new CSoldOneState(*this));
	}

	void SetHasQuarterState() override
	{
		m_currentState.reset(new CHasQuarterState(*this));
	}

	virtual void SetMaxQuarterCountState() override
	{
		m_currentState.reset(new CMaxQuarterCountState(*this));
	}

	virtual void EjectQuarters() override
	{
		std::cout << m_quarterCount << " quarters comes rolling out the slot...\n";
		m_quarterCount = 0;
	}

	virtual void RemoveQuarter() override
	{
		if (m_quarterCount)
		{
			--m_quarterCount;
		}
	}

	virtual void AddQuarter() override
	{
		++m_quarterCount;
	}

	virtual size_t GetQuarterCount() const override
	{
		return m_quarterCount;
	}

private:
	unsigned m_count = 0;
	std::unique_ptr<IState> m_currentState;
	size_t m_quarterCount = 0u;
};

