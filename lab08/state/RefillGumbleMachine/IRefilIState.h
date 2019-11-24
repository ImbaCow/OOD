#pragma once
#include "pch.h"
#include "IState.h"

struct IRefilIState : public IState
{
	virtual void Refill(size_t ballsCount) = 0;

	~IRefilIState() = default;
};