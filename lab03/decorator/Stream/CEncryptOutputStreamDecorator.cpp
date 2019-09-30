#include "pch.h"
#include "CEncryptOutputStreamDecorator.h"


CEncryptOutputStreamDecorator::CEncryptOutputStreamDecorator(std::unique_ptr<IOutputStream>&& stream, size_t key)
	: COutputStreamDecorator(std::move(stream))
	, m_encryptor(key)
{
}

void CEncryptOutputStreamDecorator::WriteByte(uint8_t data)
{
	COutputStreamDecorator::WriteByte(m_encryptor.Encrypt(data));
}

void CEncryptOutputStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	const uint8_t* buff = static_cast<const uint8_t*>(srcData);
	std::vector<uint8_t> encodedBuff(static_cast<size_t>(size));

	for (size_t i = 0; i < encodedBuff.size(); ++i)
	{
		encodedBuff[i] = m_encryptor.Encrypt(*(buff + i));
	}

	COutputStreamDecorator::WriteBlock(encodedBuff.data(), size);
}
