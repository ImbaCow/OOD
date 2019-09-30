#include "pch.h"
#include "CInputStreamDecorator.h"

CInputStreamDecorator::CInputStreamDecorator(std::unique_ptr<IInputStream>&& stream)
	: m_stream(std::move(stream))
{
}

bool CInputStreamDecorator::IsEOF() const
{
	return m_stream->IsEOF();
}

uint8_t CInputStreamDecorator::ReadByte()
{
	return m_stream->ReadByte();
}

std::streamsize CInputStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	return m_stream->ReadBlock(dstBuffer, size);
}
