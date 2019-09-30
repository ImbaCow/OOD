#include "pch.h"
#include "CDecompressInputStreamDecorator.h"

CDecompressInputStreamDecorator::CDecompressInputStreamDecorator(std::unique_ptr<IInputStream>&& stream)
	: CInputStreamDecorator(std::move(stream))
{
}

bool CDecompressInputStreamDecorator::IsEOF() const
{
	return (m_count == 0) && CInputStreamDecorator::IsEOF();
}

uint8_t CDecompressInputStreamDecorator::ReadByte()
{
	if (m_count == 0)
	{
		m_count = CInputStreamDecorator::ReadByte();
		if (!CInputStreamDecorator::IsEOF())
		{
			m_currCh = CInputStreamDecorator::ReadByte();
		}
		else
		{
			m_count = 0;
		}
	}
	if (m_count != 0)
	{
		--m_count;
	}
	return (m_currCh);
}

std::streamsize CDecompressInputStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	uint8_t* buff = static_cast<uint8_t*>(dstBuffer);

	for (std::streamsize i = 0; i < size; ++i)
	{
		if (IsEOF())
		{
			return i;
		}
		*(buff + i) = ReadByte();
	}
	return size;
}
