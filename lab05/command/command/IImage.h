#pragma once
#include "pch.h"

class IImage
{
public:
	virtual ~IImage() = default;

	virtual Path GetPath() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void Resize(int width, int height) = 0;
};