#pragma once
#include "pch.h"
#include "IInputStream.h"

class CInputStreamDecorator : public IInputStream
{
public:
	virtual ~CInputStreamDecorator() = default;

	virtual bool IsEOF() const override;
	virtual uint8_t ReadByte() override;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

protected:
	CInputStreamDecorator(std::unique_ptr<IInputStream>&& stream);

private:
	std::unique_ptr<IInputStream> m_stream;
};
