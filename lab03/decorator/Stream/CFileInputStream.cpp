#include "pch.h"
#include "CFileInputStream.h"

CFileInputStream::CFileInputStream(const std::string& fileName)
	: m_file(fileName, std::ios::binary)
	, CInputStream(m_file)
{
	if (!m_file.is_open())
	{
		throw std::ios_base::failure("input file '" + fileName + "' not found");
	}
}