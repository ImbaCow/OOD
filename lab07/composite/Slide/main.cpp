#pragma once
#include "pch.h"
#include "CEllipseShape.h"
#include "CRectangleShape.h"
#include "CShapeGroup.h"
#include "CSvgCanvas.h"
#include "CTriangleShape.h"

using namespace std;

void Test1()
{
	auto triangle1 = make_shared<CTriangleShape>(Point{ 10, 10 }, Point{ 60, 20 }, Point{ 35, 70 }, make_unique<CStyle>(), make_unique<CLineStyle>());
	triangle1->GetFillStyle()->Enable(true);
	triangle1->GetFillStyle()->SetColor(0x0000FFFF);
	triangle1->GetOutlineStyle()->Enable(true);
	triangle1->GetOutlineStyle()->SetColor(0x000000FF);
	triangle1->GetOutlineStyle()->SetLineSize(3.0);

	auto triangle2 = make_shared<CTriangleShape>(Point{ 10, 90 }, Point{ 60, 100 }, Point{ 35, 70 }, make_unique<CStyle>(), make_unique<CLineStyle>());
	triangle2->GetFillStyle()->Enable(true);
	triangle2->GetFillStyle()->SetColor(0x00FF008F);

	auto ellipse = make_shared<CEllipseShape>(Rect{ Point{ 35, 70 }, 100, 55 }, make_unique<CStyle>(), make_unique<CLineStyle>());
	ellipse->GetFillStyle()->Enable(true);
	ellipse->GetFillStyle()->SetColor(0xFF0000FF);
	ellipse->GetOutlineStyle()->Enable(true);
	ellipse->GetOutlineStyle()->SetColor(0x000000FF);
	ellipse->GetOutlineStyle()->SetLineSize(3.0);

	auto sg = make_shared<CShapeGroup>(std::vector<std::shared_ptr<IShape>>{ triangle1 });
	sg->GetFillStyle()->Enable(false);
	sg->GetOutlineStyle()->SetColor(0x00FF00FF);
	sg->GetOutlineStyle()->SetLineSize(2.0);
	sg->AddShape(ellipse);

	auto doc = std::make_shared<svg::Document>("test.svg", svg::Layout(svg::Dimensions(200, 200), svg::Layout::TopLeft));
	CSvgCanvas canvas(doc);

	triangle2->Draw(canvas);
	sg->Draw(canvas);

	doc->save();
}

void Test2()
{
	auto rectangle = make_shared<CRectangleShape>(Rect{ Point{ 10, 10 }, 50, 100 }, make_unique<CStyle>(), make_unique<CLineStyle>());
	rectangle->GetFillStyle()->Enable(true);
	rectangle->GetFillStyle()->SetColor(0x00FF00FF);
	rectangle->GetOutlineStyle()->Enable(true);
	rectangle->GetOutlineStyle()->SetColor(0x000000FF);
	rectangle->GetOutlineStyle()->SetLineSize(2.0);

	auto ellipse = make_shared<CEllipseShape>(Rect{ Point{ 40, 30 }, 50, 50 }, make_unique<CStyle>(), make_unique<CLineStyle>());
	ellipse->GetFillStyle()->Enable(true);
	ellipse->GetFillStyle()->SetColor(0xFFFF00FF);
	ellipse->GetOutlineStyle()->Enable(true);
	ellipse->GetOutlineStyle()->SetColor(0x000000FF);
	ellipse->GetOutlineStyle()->SetLineSize(3.0);

	auto sg = make_shared<CShapeGroup>(std::vector<std::shared_ptr<IShape>>{ rectangle,
		ellipse });
	sg->SetFrame({ { 150, 150 }, 40, 45 });

	auto doc = std::make_shared<svg::Document>("test.svg", svg::Layout(svg::Dimensions(400, 400), svg::Layout::TopLeft));
	CSvgCanvas canvas(doc);

	sg->Draw(canvas);

	doc->save();
}

int main()
{
	Test1();
}
