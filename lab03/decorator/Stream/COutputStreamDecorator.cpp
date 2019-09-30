#pragma once
#include "pch.h"
#include "COutputStreamDecorator.h"

COutputStreamDecorator::COutputStreamDecorator(std::unique_ptr<IOutputStream>&& stream)
	: m_stream(std::move(stream))
{
}

void COutputStreamDecorator::WriteByte(uint8_t data)
{
	m_stream->WriteByte(data);
}

void COutputStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	m_stream->WriteBlock(srcData, size);
}
