#pragma once
#include "CInputStreamDecorator.h"

class CDecompressInputStreamDecorator : public CInputStreamDecorator
{
public:
	CDecompressInputStreamDecorator(std::unique_ptr<IInputStream>&& stream);
	virtual ~CDecompressInputStreamDecorator() = default;

	virtual bool IsEOF() const override;
	virtual uint8_t ReadByte() override;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	uint8_t m_currCh;
	size_t m_count = 0;
};
