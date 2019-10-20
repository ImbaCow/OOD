#include "pch.h"
#include "CImage.h"
#include "CResizeImageCommand.h"

CImage::CImage(CCommandHistory& history, const Path& path, int width, int height)
	: m_history(history)
	, m_path(path)
	, m_width(width)
	, m_height(height)
{
}

CImage::~CImage()
{
	std::filesystem::remove(m_path);
}

Path CImage::GetPath() const
{
	return m_path;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	std::unique_ptr<ICommand> commandPtr = std::make_unique<CResizeImageCommand>(m_width, m_height, width, height);
	m_history.ExecuteCommand(std::move(commandPtr));
}
