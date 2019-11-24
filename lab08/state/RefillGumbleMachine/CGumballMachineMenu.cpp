#include "pch.h"
#include "CGumballMachineMenu.h"

using namespace std;

namespace
{
optional<size_t> ParseNum(const string& numStr)
{
	optional<size_t> result = nullopt;
	if (numStr.size() && all_of(numStr.begin(), numStr.end(), isdigit))
	{
		result = stoull(numStr);
	}

	return result;
}
} // namespace

CGumballMachineMenu::CGumballMachineMenu()
	: m_menu(cin, cout)
{
	AddCommand("EjectQuarter", "Eject all quarters in the machine", &CGumballMachineMenu::EjectQuarter);
	AddCommand("InsertQuarter", "Insert quarter into the machine", &CGumballMachineMenu::InsertQuarter);
	AddCommand("TurnCrank", "Try to get gumball from machine", &CGumballMachineMenu::TurnCrank);
	AddCommand("ToString", "Get state of the machine", &CGumballMachineMenu::ToString);
	AddCommand("Refill", "Refill <count>. Refill machine with balls", &CGumballMachineMenu::Refill);
	m_menu.AddCommand("Help", "Help", [this](std::istream&) { m_menu.ShowCommands(); });
	m_menu.AddCommand("Exit", "Exit", [this](std::istream&) { m_menu.Exit(); });
}

void CGumballMachineMenu::Run()
{
	optional<size_t> gumballCount = nullopt;
	do
	{
		string argStr;
		cout << "Enter start gumball count: ";
		getline(cin, argStr);
		gumballCount = ParseNum(argStr);
		if (!gumballCount)
		{
			cout << "Invalid balls count argument : '" + argStr + '\'' << endl;
		}
		else
		{
			break;
		}
	} while (true);
	m_gumballMachine.reset(new CRefillGumballMachine(gumballCount.value()));
	cout << endl;
	m_menu.Run();
}

void CGumballMachineMenu::AddCommand(const std::string& shortcut, const std::string& description, Command handler)
{
	m_menu.AddCommand(shortcut, description, std::bind(handler, this, std::placeholders::_1));
}

void CGumballMachineMenu::EjectQuarter(std::istream&)
{
	m_gumballMachine->EjectQuarter();
}

void CGumballMachineMenu::InsertQuarter(std::istream&)
{
	m_gumballMachine->InsertQuarter();
}

void CGumballMachineMenu::Refill(std::istream& input)
{
	string argStr;
	getline(input >> ws, argStr);
	optional<size_t> ballsCount = ParseNum(argStr);
	if (!ballsCount)
	{
		throw invalid_argument("Invalid balls count argument: '" + argStr + '\'');
	}
	m_gumballMachine->Refill(ballsCount.value());
}

void CGumballMachineMenu::ToString(std::istream&)
{
	cout << m_gumballMachine->ToString();
}

void CGumballMachineMenu::TurnCrank(std::istream&)
{
	m_gumballMachine->TurnCrank();
}
