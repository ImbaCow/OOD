#pragma once
class ReplaceEncryptor
{
public:
	ReplaceEncryptor(size_t key);

	uint8_t Encrypt(uint8_t ch);
	uint8_t Decrypt(uint8_t ch);

private:
	std::vector<uint8_t> encodeArr;
	std::vector<uint8_t> decodeArr;
};
