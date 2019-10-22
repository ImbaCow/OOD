#pragma once
#include "IOutputStream.h"

class COutputStreamDecorator : public IOutputStream
{
public:
	virtual ~COutputStreamDecorator() = default;

	virtual void WriteByte(uint8_t data) override;
	virtual void WriteBlock(const void* srcData, std::streamsize size) override;

protected:
	COutputStreamDecorator(std::unique_ptr<IOutputStream>&& stream);

private:
	std::unique_ptr<IOutputStream> m_stream;
};
