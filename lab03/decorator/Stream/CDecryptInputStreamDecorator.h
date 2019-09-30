#pragma once
#include "pch.h"
#include "ReplaceEncryptor.h"
#include "CInputStreamDecorator.h"

class CDecryptInputStreamDecorator : public CInputStreamDecorator
{
public:
	CDecryptInputStreamDecorator(std::unique_ptr<IInputStream>&& stream, size_t key);
	virtual ~CDecryptInputStreamDecorator() = default;

	virtual uint8_t ReadByte() override;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	ReplaceEncryptor m_encryptor;
};
