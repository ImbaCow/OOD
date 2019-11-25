#include "pch.h"
#include "catch2/catch.hpp"
#include "CMultiNaiveGumballMachine.h"
#include "CoutRedirect.h"

using namespace std;

string InsertQuarter(CMultiNaiveGumballMachine& machine)
{
	stringstream ss;
	CoutRedirect buff(ss.rdbuf());
	machine.InsertQuarter();

	return ss.str();
}
string EjectQuarter(CMultiNaiveGumballMachine& machine)
{
	stringstream ss;
	CoutRedirect buff(ss.rdbuf());
	machine.EjectQuarter();

	return ss.str();
}
string TurnCrank(CMultiNaiveGumballMachine& machine)
{
	stringstream ss;
	CoutRedirect buff(ss.rdbuf());
	machine.TurnCrank();

	return ss.str();
}

SCENARIO("Naive gumball machine can work")
{
	GIVEN("new gumball machine with gumballs")
	{
		CMultiNaiveGumballMachine machine(20u);
		REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs, 0 quarters
Machine is waiting for quarter
)");

		WHEN("eject quarter")
		{
			{
				string message = EjectQuarter(machine);
				THEN("state not changed and error message given")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs, 0 quarters
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
Inventory: 20 gumballs, 0 quarters
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
Inventory: 20 gumballs, 1 quarters
Machine is waiting for turn of crank or insert of quarter
)");
					REQUIRE(message == R"(You inserted a quarter
)");
				}
			}

			AND_WHEN("insert quarter")
			{
				{
					string message = InsertQuarter(machine);
					THEN("state quarter count increased and insert message given")
					{
						REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs, 2 quarters
Machine is waiting for turn of crank or insert of quarter
)");
						REQUIRE(message == R"(You inserted another quarter
)");
					}
				}

				AND_WHEN("eject quarter")
				{

					{
						string message = EjectQuarter(machine);
						THEN("state quarter count set to 0 and eject message given")
						{
							REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs, 0 quarters
Machine is waiting for quarter
)");
							REQUIRE(message == R"(2 quarters comes rolling out the slot...
)");
						}
					}
				}

				AND_WHEN("insert max count quarters")
				{

					{
						string message;
						for (size_t i = 0; i < 3; ++i)
						{
							message += InsertQuarter(machine);
						}

						THEN("state quarter count decreased and eject message given")
						{
							REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs, 5 quarters
Machine is waiting for turn of crank with maximum quarters
)");
							REQUIRE(message == R"(You inserted another quarter
You inserted another quarter
You inserted another quarter
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
Inventory: 20 gumballs, 5 quarters
Machine is waiting for turn of crank with maximum quarters
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

							THEN("state changed to no quarter")
							{
								REQUIRE(machine.ToString() == R"(
Inventory: 20 gumballs, 0 quarters
Machine is waiting for quarter
)");
								REQUIRE(message == R"(5 quarters comes rolling out the slot...
)");
							}
						}
					}

					AND_WHEN("turn crank")
					{
						{
							string message = TurnCrank(machine);

							THEN("state changed and quarter count with ball count decreased")
							{
								REQUIRE(machine.ToString() == R"(
Inventory: 19 gumballs, 4 quarters
Machine is waiting for turn of crank or insert of quarter
)");
								REQUIRE(message == R"(You turned...
A gumball comes rolling out the slot...
)");
							}
						}
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
Inventory: 20 gumballs, 0 quarters
Machine is waiting for quarter
)");
						REQUIRE(message == R"(1 quarters comes rolling out the slot...
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
Inventory: 19 gumballs, 0 quarters
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
		CMultiNaiveGumballMachine machine(0u);
		REQUIRE(machine.ToString() == R"(
Inventory: 0 gumballs, 0 quarters
Machine is sold out
)");

		WHEN("eject quarter")
		{
			{
				string message = EjectQuarter(machine);
				THEN("state not changed and error message given")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 0 gumballs, 0 quarters
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
Inventory: 0 gumballs, 0 quarters
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
Inventory: 0 gumballs, 0 quarters
Machine is sold out
)");
					REQUIRE(message == R"(You turned but there's no gumballs
)");
				}
			}
		}
	}
	GIVEN("new gumball machine with 1 ball an quarter")
	{
		CMultiNaiveGumballMachine machine(1u);
		{
			string message = InsertQuarter(machine);
		}

		WHEN("turn crank")
		{
			{
				string message = TurnCrank(machine);
				THEN("sold out message given")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 0 gumballs, 0 quarters
Machine is sold out
)");
					REQUIRE(message == R"(You turned...
A gumball comes rolling out the slot...
Oops, out of gumballs
)");
				}
			}
		}

		WHEN("insert quarter and turn crank")
		{
			{
				string message = InsertQuarter(machine);
				message = TurnCrank(machine);

				THEN("sold out state and quarter count saved")
				{
					REQUIRE(machine.ToString() == R"(
Inventory: 0 gumballs, 1 quarters
Machine is sold out
)");
					REQUIRE(message == R"(You turned...
A gumball comes rolling out the slot...
Oops, out of gumballs
)");
				}
			}
		}
	}
}
