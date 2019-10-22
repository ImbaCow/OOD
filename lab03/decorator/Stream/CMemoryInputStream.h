#pragma once
#include "CInputStream.h"

class CMemoryInputStream : public CInputStream
{
public:
	CMemoryInputStream(std::istringstream& stream);
	virtual ~CMemoryInputStream() = default;
};
