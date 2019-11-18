#include "pch.h"
#include "CMultiGumballMachine.h"
#include "CMultiNaiveGumballMachine.h"

void TestStateMachine()
{
	CMultiGumballMachine mac(6);
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.EjectQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.TurnCrank();
	mac.TurnCrank();
	mac.TurnCrank();
	mac.TurnCrank();
	mac.TurnCrank();
	mac.TurnCrank();
}

void TestNaiveMachine()
{
	CMultiNaiveGumballMachine mac(6);
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.EjectQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.TurnCrank();
	mac.TurnCrank();
	mac.TurnCrank();
	mac.TurnCrank();
	mac.TurnCrank();
	mac.TurnCrank();
}

int main()
{
	TestNaiveMachine();
}
