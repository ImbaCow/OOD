#include "pch.h"
#include "CMultiGumballMachine.h"

int main()
{
	CMultiGumballMachine mac(6);
	mac.InsertQuarter();
	mac.InsertQuarter();
	mac.TurnCrank();
	mac.TurnCrank();
}
