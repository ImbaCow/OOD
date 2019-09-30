#include "pch.h"
#include "CInputStream.h"

CInputStream::CInputStream(std::istream& stream)
	: m_stream(stream)
{
}

bool CInputStream::IsEOF() const
{
	return m_stream.eof();
}

uint8_t CInputStream::ReadByte()
{
	if (IsEOF())
	{
		throw std::ios_base::failure("Read when is eof");
	}
	return static_cast<uint8_t>(m_stream.get());
}

std::streamsize CInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	return m_stream.readsome(static_cast<char*>(dstBuffer), size);
}
