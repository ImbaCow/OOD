#pragma once
#include "pch.h"
#include "IGumballMachine.h"

struct IMultiGumballMachine : public IGumballMachine
{
	virtual void ReleaseQuarter() = 0;
	virtual void AddQuarter() = 0;
	virtual size_t GetQuarterCount() const = 0;

	virtual void SetMaxQuarterCountState() = 0;

	virtual ~IMultiGumballMachine() = default;
};