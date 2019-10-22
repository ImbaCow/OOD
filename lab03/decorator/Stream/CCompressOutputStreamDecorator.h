#pragma once
#include "COutputStreamDecorator.h"

class CCompressOutputStreamDecorator : public COutputStreamDecorator
{
public:
	CCompressOutputStreamDecorator(std::unique_ptr<IOutputStream>&& stream);
	~CCompressOutputStreamDecorator();

	virtual void WriteByte(uint8_t data) override;
	virtual void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	uint8_t m_currCh;
	size_t m_count = 0;

	void FlushByte();
};
