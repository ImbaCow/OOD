#pragma once 
#include "pch.h"
#include "CPainter.h"

void CPainter::DrawPicture(const CPictureDraft& draft, ICanvas& canvas) const
{
	for (size_t i = 0; i < draft.GetShapeCount(); ++i)
	{
		draft.GetShape(i)->Draw(canvas);
	}
}
