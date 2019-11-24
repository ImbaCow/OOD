#pragma once
#include "pch.h"
#include "IRefilIState.h"
#include "IRefillGumballMachine.h"

class CMaxQuarterCountState : public IRefilIState
{
public:
	CMaxQuarterCountState(IRefillGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		std::cout << "You can't insert another quarter\n";
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
		return "waiting for turn of crank with maximum quarters";
	}

	void Refill(size_t ballsCount) override
	{
		m_gumballMachine.AddBalls(ballsCount);
	}

private:
	IRefillGumballMachine& m_gumballMachine;
};

