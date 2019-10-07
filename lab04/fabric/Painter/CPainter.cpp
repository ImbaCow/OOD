#pragma once 
#include "pch.h"
#include "CPainter.h"

void CPainter::DrawPicture(const CPictureDraft& draft, std::shared_ptr<ICanvas>& canvas)
{
	for (size_t i = 0; i < draft.GetShapeCount(); ++i)
	{
		draft.GetShape(i)->Draw(canvas);
	}
}
