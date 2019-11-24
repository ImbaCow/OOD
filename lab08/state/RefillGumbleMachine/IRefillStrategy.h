#pragma once
#include "pch.h"

struct IRefillStrategy
{
	virtual void AddBalls(size_t ballsCount) = 0;

	virtual ~IRefillStrategy() = default;
};