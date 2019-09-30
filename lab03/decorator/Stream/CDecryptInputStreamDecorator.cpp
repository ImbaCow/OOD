#pragma once
#include "pch.h"
#include "CDecryptInputStreamDecorator.h"

CDecryptInputStreamDecorator::CDecryptInputStreamDecorator(std::unique_ptr<IInputStream>&& stream, size_t key)
	: CInputStreamDecorator(std::move(stream))
	, m_encryptor(key)
{
}

uint8_t CDecryptInputStreamDecorator::ReadByte()
{
	return m_encryptor.Decrypt(CInputStreamDecorator::ReadByte());
}

std::streamsize CDecryptInputStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	std::streamsize newSize = CInputStreamDecorator::ReadBlock(dstBuffer, size);
	uint8_t* buff = static_cast<uint8_t*>(dstBuffer);

	for (size_t i = 0; i < newSize; ++i)
	{
		uint8_t ch = *(buff + i);
		*(buff + i) = m_encryptor.Decrypt(ch);
	}
	return newSize;
}
