#include "pch.h"
#include "CMemoryInputStream.h"

CMemoryInputStream::CMemoryInputStream(std::istringstream& stream)
	: CInputStream(stream)
{
}