#pragma once
#include "ReplaceEncryptor.h"
#include "COutputStreamDecorator.h"

class CEncryptOutputStreamDecorator : public COutputStreamDecorator
{
public:
	CEncryptOutputStreamDecorator(std::unique_ptr<IOutputStream>&& stream, size_t key);
	virtual ~CEncryptOutputStreamDecorator() = default;

	virtual void WriteByte(uint8_t data) override;
	virtual void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	ReplaceEncryptor m_encryptor;
};
