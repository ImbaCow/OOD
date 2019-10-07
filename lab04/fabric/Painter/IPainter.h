#pragma once
#include "pch.h"
#include "CPictureDraft.h"
#include "ICanvas.h"

class IPainter
{
public:
	virtual ~IPainter() = default;

	virtual void DrawPicture(const CPictureDraft& draft, std::shared_ptr<ICanvas>& canvas) = 0;
};
