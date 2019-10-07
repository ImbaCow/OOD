#pragma once
#include "pch.h"
#include "IPainter.h"

class CPainter : public IPainter
{
public:
	virtual ~CPainter() = default;

	virtual void DrawPicture(const CPictureDraft& draft, std::shared_ptr<ICanvas>& canvas) override;
};
