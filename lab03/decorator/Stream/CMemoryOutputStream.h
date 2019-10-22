#pragma once
#include "COutputStream.h"

class CMemoryOutputStream : public COutputStream
{
public:
	CMemoryOutputStream(std::ostringstream& stream);
	virtual ~CMemoryOutputStream() = default;
};
