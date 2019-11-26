#pragma once
#include "CPictureDraft.h"
#include "ICanvas.h"

class CPainter
{
public:
	void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) const;
};
