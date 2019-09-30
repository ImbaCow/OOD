#include "pch.h"
#include "CMemoryOutputStream.h"

CMemoryOutputStream::CMemoryOutputStream(std::ostringstream& stream)
	: COutputStream(stream)
{
}
