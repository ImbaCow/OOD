#include "pch.h"
#include "ReplaceEncryptor.h"

ReplaceEncryptor::ReplaceEncryptor(size_t key)
	: encodeArr(UINT8_MAX + 1)
	, decodeArr(encodeArr.size())
{
	std::iota(encodeArr.begin(), encodeArr.end(), '\0');
	std::shuffle(encodeArr.begin(), encodeArr.end(), std::mt19937(static_cast<uint32_t>(key)));
	for (size_t i = 0; i < encodeArr.size(); ++i)
	{
		decodeArr[encodeArr[i]] = static_cast<uint8_t>(i);
	}
}

uint8_t ReplaceEncryptor::Encrypt(uint8_t ch)
{
	return encodeArr[ch];
}

uint8_t ReplaceEncryptor::Decrypt(uint8_t ch)
{
	return decodeArr[ch];
}
