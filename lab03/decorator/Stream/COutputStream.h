#pragma once
#include "IOutputStream.h"

class COutputStream : public IOutputStream
{
public:
	COutputStream(std::ostream& stream);
	virtual ~COutputStream() = default;

	virtual void WriteByte(uint8_t data) override;
	virtual void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::ostream& m_stream;
};
