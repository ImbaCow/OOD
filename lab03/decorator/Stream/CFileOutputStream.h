#pragma once
#include "COutputStream.h"

class CFileOutputStream : public COutputStream
{
public:
	CFileOutputStream(const std::string& fileName);
	virtual ~CFileOutputStream() = default;

private:
	std::ofstream m_file;
};
