#include "pch.h"
#include "CFileOutputStream.h"

CFileOutputStream::CFileOutputStream(const std::string& fileName)
	: COutputStream(m_file) 
	, m_file(fileName, std::ios::binary)
{
	if (!m_file.is_open())
	{
		throw std::ios_base::failure("output file '" + fileName + "' not found");
	}
}
