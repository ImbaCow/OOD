#pragma once
#include "pch.h"
#include "CDesigner.h"
#include "CPainter.h"
#include "CSvgCanvas.h"
#include "CShapeFactory.h"

using namespace std;

int main()
{
	try
	{
		shared_ptr<IShapeFactory> factory = make_shared<CShapeFactory>();
		CDesigner designer(factory);
		CPainter painter;

		CPictureDraft draft = designer.CreateDraft(cin);
		CSvgCanvas canvas("test.svg", 100, 100, 2);
		painter.DrawPicture(draft, canvas);
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
	}
}
