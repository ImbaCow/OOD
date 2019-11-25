#pragma once
#include "pch.h"

struct CoutRedirect
{
	CoutRedirect(std::streambuf* new_buffer)
		: old(std::cout.rdbuf(new_buffer))
	{
	}

	~CoutRedirect()
	{
		std::cout.rdbuf(old);
	}

private:
	std::streambuf* old;
};