#pragma once
#include "pch.h"
#include "COutputStream.h"

class CMemoryOutputStream : public COutputStream
{
public:
	CMemoryOutputStream(std::ostringstream& stream);
	virtual ~CMemoryOutputStream() = default;
};
