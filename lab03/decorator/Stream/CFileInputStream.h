#pragma once
#include "CInputStream.h"

class CFileInputStream : public CInputStream
{
public:
	CFileInputStream(const std::string& fileName);
	virtual ~CFileInputStream() = default;

private:
	std::ifstream m_file;
};
