#pragma once
#include "pch.h"
#include "IInputStream.h"

class CInputStream : public IInputStream
{
public:
	CInputStream(std::istream& stream);
	virtual ~CInputStream() = default;

	virtual bool IsEOF() const override;
	virtual uint8_t ReadByte() override;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::istream& m_stream;
};
