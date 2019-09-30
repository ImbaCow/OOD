#include "pch.h"
#include "COutputStream.h"

COutputStream::COutputStream(std::ostream& stream)
	: m_stream(stream)
{
}

void COutputStream::WriteByte(uint8_t data)
{
	m_stream.put(data);
}

void COutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	const char* buff = static_cast<const char*>(srcData);
	m_stream.write(buff, size);
}
