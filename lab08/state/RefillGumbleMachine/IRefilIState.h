#pragma once
#include "pch.h"
#include "IState.h"

//TODO ������ IRefilIState
struct IRefilIState : public IState
{
	virtual void Refill(size_t ballsCount) = 0;

	~IRefilIState() = default;
};