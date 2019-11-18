#pragma once
#include "pch.h"

class CMultiNaiveGumballMachine
{
public:
	const size_t MAX_QUARTER_COUNT = 5u;
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
		MaxQuarterCount,// Количество монет максимально
	};

	CMultiNaiveGumballMachine(unsigned count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			++m_quarterCount;
			cout << "You inserted a quarter\n";
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			++m_quarterCount;
			std::cout << "You inserted another quarter\n";
			if (m_quarterCount >= 5)
			{
				m_state = State::MaxQuarterCount;
			}
			break;
		case State::Sold:
			cout << "Please wait, we're already giving you a gumball\n";
			break;
		case State::MaxQuarterCount:
			cout << "You can't insert another quarter\n";
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
		case State::MaxQuarterCount:
			cout << m_quarterCount << " quarters comes rolling out the slot...\n";
			m_quarterCount = 0;
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			cout << "Please wait, we're already giving you a gumball\n";
			break;
		case State::SoldOut:
			if (m_quarterCount)
			{
				std::cout << m_quarterCount << " quarters comes rolling out the slot...\n";
				m_quarterCount = 0;
			}
			else
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			}
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
		case State::MaxQuarterCount:
			cout << "You turned...\n";
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_count = numBalls;
		m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
	}

	std::string ToString()const
	{
		std::string state =
			(m_state == State::SoldOut) ? "sold out" :
			(m_state == State::NoQuarter) ? "waiting for quarter" :
			(m_state == State::HasQuarter) ? "waiting for turn of crank with " + std::to_string(m_quarterCount) + " quarters" :
			(m_state == State::MaxQuarterCount) ? "waiting for turn of crank with maximum quarters"
			: "delivering a gumball";
		auto fmt = boost::format(R"(
Inventory: %1% gumballs, %2% quarters 
Machine is %3%
)");
		return (fmt % m_count % m_quarterCount % state).str();
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			--m_count;
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_quarterCount;
			if (m_count == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else if (m_quarterCount)
			{
				m_state = State::HasQuarter;
			}
			else
			{
				m_state = State::NoQuarter;
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
		case State::MaxQuarterCount:
			cout << "No gumball dispensed\n";
			break;
		}
	}

	unsigned m_count;	// Количество шариков
	State m_state = State::SoldOut;
	size_t m_quarterCount = 0u;
};
