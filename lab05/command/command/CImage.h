#pragma once
#include "pch.h"
#include "IImage.h"
#include "CCommandHistory.h"

class CImage : public IImage
{
public:
	CImage(CCommandHistory& history, const Path& path, int width, int height);
	virtual ~CImage();

	virtual Path GetPath() const override;
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;
	virtual void Resize(int width, int height) override;

private:
	CCommandHistory& m_history;
	Path m_path;
	int m_width;
	int m_height;
};
