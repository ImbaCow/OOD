#include "pch.h"
#include "catch2/catch.hpp"
#include "CNaiveGumbalMachine.h"
#include "CoutRedirect.h"

using namespace std;

string InsertQuarter(CNaiveGumballMachine& machine)
{
	stringstream ss;
	CoutRedirect buff(ss.rdbuf());
	machine.InsertQuarter();

	return ss.str();
}
string EjectQuarter(CNaiveGumballMachine& machine)
{
	stringstream ss;
	CoutRedirect buff(ss.rdbuf());
	machine.EjectQuarter();

	return ss.str();
}
string TurnCrank(CNaiveGumballMachine& machine)
{
	stringstream ss;
	CoutRedirect buff(ss.rdbuf());
	machine.TurnCrank();

	return ss.str();
}

SCENARIO("Naive gumball machine can work")
{
	GIVEN("new gumball machine")
	{
		CNaiveGumballMachine machine(20u);
		REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs
Machine is waiting for quarter
)");

		WHEN("eject quarter")
		{
			{
				string message = EjectQuarter(machine);
				THEN("state not changed and error message given")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs
Machine is waiting for quarter
)");
					REQUIRE(message == R"(You haven't inserted a quarter
)");
				}
			}
		}

		WHEN("turn crank")
		{
			{
				string message = TurnCrank(machine);
				THEN("state not changed and error message given")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs
Machine is waiting for quarter
)");
					REQUIRE(message == R"(You turned but there's no quarter
)");
				}
			}
		}

		WHEN("insert quarter")
		{
			{
				string message = InsertQuarter(machine);
				THEN("state changed to waiting and quarter message given")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs
Machine is waiting for turn of crank
)");
					REQUIRE(message == R"(You inserted a quarter
)");
				}
			}

			AND_WHEN("insert quarter")
			{
				{
					string message = InsertQuarter(machine);
					THEN("state not changed and error message given")
					{
						REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs
Machine is waiting for turn of crank
)");
						REQUIRE(message == R"(You can't insert another quarter
)");
					}
				}
			}

			AND_WHEN("eject quarter")
			{
				{
					string message = EjectQuarter(machine);
					THEN("state changed to initial and quarter return message given")
					{
						REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs
Machine is waiting for quarter
)");
						REQUIRE(message == R"(Quarter returned
)");
					}
				}
			}

			AND_WHEN("turn crank")
			{
				{
					string message = TurnCrank(machine);
					THEN("state changed to initial with less balls and turn message given")
					{
						REQUIRE(machine.ToString() == R"(
Inventory: 19 gumballs
Machine is waiting for quarter
)");
						REQUIRE(message == R"(You turned...
A gumball comes rolling out the slot...
)");
					}
				}
			}
		}
	}
	GIVEN("new gumball machine with 0 ball")
	{
		CNaiveGumballMachine machine(0u);
		REQUIRE(machine.ToString() == R"(
Inventory: 0 gumballs
Machine is sold out
)");

		WHEN("eject quarter")
		{
			{
				string message = EjectQuarter(machine);
				THEN("state not changed and error message given")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 0 gumballs
Machine is sold out
)");
					REQUIRE(message == R"(You can't eject, you haven't inserted a quarter yet
)");
				}
			}
		}

		WHEN("insert quarter")
		{
			{
				string message = InsertQuarter(machine);
				THEN("state not changed and error message given")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 0 gumballs
Machine is sold out
)");
					REQUIRE(message == R"(You can't insert a quarter, the machine is sold out
)");
				}
			}
		}

		WHEN("turn crank")
		{
			{
				string message = TurnCrank(machine);
				THEN("state not changed and error message given")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 0 gumballs
Machine is sold out
)");
					REQUIRE(message == R"(You turned but there's no gumballs
)");
				}
			}
		}

		WHEN("refill machine")
		{
			machine.Refill(5u);
			THEN("state not changed and error message given")
			{
				REQUIRE(machine.ToString() == R"(
Inventory: 5 gumballs
Machine is waiting for quarter
)");
			}
		}
	}
}
