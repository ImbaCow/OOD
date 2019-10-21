#pragma once
#include "pch.h"
#include "IImage.h"
#include "ExecuteCommandFunc.h"

class CImage : public IImage
{
public:
	CImage(ExecuteCommandFunc executeCommandFunc, const Path& path, int width, int height);
	virtual ~CImage();

	virtual Path GetPath() const override;
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;
	virtual void Resize(int width, int height) override;

private:
	ExecuteCommandFunc m_executeCommandFunc;
	Path m_path;
	int m_width;
	int m_height;
};
