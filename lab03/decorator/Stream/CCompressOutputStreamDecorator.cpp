#include "pch.h"
#include "CCompressOutputStreamDecorator.h"

CCompressOutputStreamDecorator::CCompressOutputStreamDecorator(std::unique_ptr<IOutputStream>&& stream)
	: COutputStreamDecorator(std::move(stream))
{
}

CCompressOutputStreamDecorator::~CCompressOutputStreamDecorator()
{
	FlushByte();
}

void CCompressOutputStreamDecorator::WriteByte(uint8_t data)
{
	if (data != m_currCh || m_count >= UINT8_MAX)
	{
		FlushByte();
		m_currCh = data;
	}
	++m_count;
}

void CCompressOutputStreamDecorator::FlushByte()
{
	if (m_count > 0)
	{
		COutputStreamDecorator::WriteByte(static_cast<uint8_t>(m_count));
		COutputStreamDecorator::WriteByte(m_currCh);
		m_count = 0;
	}
}

void CCompressOutputStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	const uint8_t* buff = static_cast<const uint8_t*>(srcData);
	std::vector<uint8_t> compressedBuff;
	
	for (std::streamsize i = 0; i < size; ++i)
	{
		uint8_t ch = *(buff + i);
		WriteByte(ch);
	}
}
