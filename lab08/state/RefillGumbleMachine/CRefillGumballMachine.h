#pragma once
#include "pch.h"
#include "CMaxQuarterCountState.h"
#include "CHasQuarterState.h"
#include "CNoQuarterState.h"
#include "CSoldOutState.h"
#include "CSoldState.h"

class CRefillGumballMachine : private IRefillGumballMachine
{
public:
	CRefillGumballMachine(size_t numBalls)
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

	void Refill(size_t numBalls)
	{
		m_currentState->Refill(numBalls);
	}

	std::string ToString() const
	{
		auto fmt = boost::format(R"(
Inventory: %1% gumballs, %2% quarters 
Machine is %3%
)");
		return (fmt % m_count % m_quarterCount % m_currentState->ToString()).str();
	}

private:
	size_t GetBallCount() const override
	{
		return m_count;
	}

	void ReleaseBall() override
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

	void SetMaxQuarterCountState() override
	{
		m_currentState.reset(new CMaxQuarterCountState(*this));
	}

	void EjectQuarters() override
	{
		std::cout << m_quarterCount << " quarters comes rolling out the slot...\n";
		m_quarterCount = 0;
	}

	void RemoveQuarter() override
	{
		if (m_quarterCount)
		{
			--m_quarterCount;
		}
	}

	void AddQuarter() override
	{
		++m_quarterCount;
	}

	size_t GetQuarterCount() const override
	{
		return m_quarterCount;
	}

	void AddBalls(size_t ballsCount) override
	{
		++m_count;
		std::cout << "Filled with " << ballsCount << " balls\n";
	}

private:
	size_t m_count = 0u;
	std::unique_ptr<IRefilIState> m_currentState;
	size_t m_quarterCount = 0u;
};
