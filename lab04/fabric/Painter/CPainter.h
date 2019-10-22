#pragma once
#include "CPictureDraft.h"
#include "ICanvas.h"

class CPainter
{
public:
	virtual ~CPainter() = default;

	virtual void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) const;
};
