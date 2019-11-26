#pragma once
#include "pch.h"
#include "CRectangleShape.h"
#include "CShapeGroup.h"
#include "TestUtils.h"
#include "TestCanvas.h"

using namespace Catch::Matchers::Floating;
using namespace std;

SCENARIO("Group shape can be created and resized")
{
	GIVEN("A group shape with 1 shape")
	{
		Point p1{ 10.0, 6.0 };
		auto shape = make_shared<CRectangleShape>(Rect{ p1, 180.0, 9.0 }, make_unique<CStyle>(), make_unique<CLineStyle>());
		CShapeGroup sg({ shape });

		RequirePointEquality(sg.GetFrame().value().leftTop, { 10.0, 6.0 });
		RequireDoubleEquality(sg.GetFrame().value().width, 180.0);
		RequireDoubleEquality(sg.GetFrame().value().height, 9.0);

		WHEN("shape group is moved and resized")
		{
			sg.SetFrame({ { 150.0, 96.0 }, 90.0, 18.0 });
			THEN("rectangle is moved and resized")
			{
				CheckPointEquality(shape->GetLeftTop(), { 150.0, 96.0 });
				CheckDoubleEquality(shape->GetWidth(), 90.0);
				CheckDoubleEquality(shape->GetHeight(), 18.0);
			}
		}
	}

	GIVEN("A group shape with mulltiple shape")
	{
		auto shape1 = make_shared<CRectangleShape>(Rect{ Point{ 1.0, 2.0 }, 180.0, 18.0 }, make_unique<CStyle>(), make_unique<CLineStyle>());
		auto shape2 = make_shared<CRectangleShape>(Rect{ Point{ .0, .0 }, .0, .0 }, make_unique<CStyle>(), make_unique<CLineStyle>());
		auto shape3 = make_shared<CRectangleShape>(Rect{ Point{ 3.0, 6.0 }, 360.0, 9.0 }, make_unique<CStyle>(), make_unique<CLineStyle>());
		CShapeGroup sg({ shape1, shape2, shape3 });

		RequirePointEquality(sg.GetFrame().value().leftTop, { .0, .0 });
		RequireDoubleEquality(sg.GetFrame().value().width, 360.0);
		RequireDoubleEquality(sg.GetFrame().value().height, 18.0);

		WHEN("shape group is moved and resized")
		{
			sg.SetFrame({ { 150.0, 96.0 }, 90.0, 18.0 });
			THEN("rectangle1 is moved and resized")
			{
				CheckPointEquality(shape1->GetLeftTop(), { 150.25, 98.0 });
				CheckDoubleEquality(shape1->GetWidth(), 45.0);
				CheckDoubleEquality(shape1->GetHeight(), 18.0);
			}

			THEN("rectangle2 is moved and resized")
			{
				CheckPointEquality(shape2->GetLeftTop(), { 150.0, 96.0 });
				CheckDoubleEquality(shape2->GetWidth(), 0.0);
				CheckDoubleEquality(shape2->GetHeight(), 0.0);
			}

			THEN("rectangle2 is moved and resized")
			{
				CheckPointEquality(shape3->GetLeftTop(), { 150.75, 102.0 });
				CheckDoubleEquality(shape3->GetWidth(), 90.0);
				CheckDoubleEquality(shape3->GetHeight(), 9.0);
			}
		}
	}

	GIVEN("A group shape with 0 shape")
	{
		CShapeGroup sg({});

		CHECK(!sg.GetFrame().has_value());

		WHEN("try to move and resize")
		{
			sg.SetFrame({ { 150.0, 96.0 }, 90.0, 18.0 });
			THEN("not moved and not resized")
			{
				CHECK(!sg.GetFrame().has_value());
			}
		}
	}
}

SCENARIO("Shape group can be drawn")
{
	GIVEN("canvas")
	{
		std::ostringstream out;
		TestCanvas canvas(out);

		AND_GIVEN("filled shape")
		{
			auto shape1 = make_shared<CRectangleShape>(Rect{ Point{ 1.0, 2.0 }, 180.0, 18.0 }, make_unique<CStyle>(0xFF00FF0F), make_unique<CLineStyle>(0xFFF000F0, 1.3));
			auto shape2 = make_shared<CRectangleShape>(Rect{ Point{ .0, .0 }, .0, .0 }, make_unique<CStyle>(0x00FF00FF), make_unique<CLineStyle>(0xF0F0F0F0, 1.4));
			auto shape3 = make_shared<CRectangleShape>(Rect{ Point{ 3.0, 6.0 }, 360.0, 9.0 }, make_unique<CStyle>(0x00000000), make_unique<CLineStyle>(0x00FF000F, 113.0));
			CShapeGroup sg({ shape1, shape2, shape3 });

			WHEN("call shape draw")
			{
				sg.Draw(canvas);

				THEN("canvas contain shape")
				{
					CHECK(out.str() == R"(fillColor:4278255375
fillPolygon:181.0/2.0;181.0/20.0;1.0/20.0;1.0/2.0;
lineColor:4293918960
lineSize:1.3
line:1.0/2.0;181.0/2.0
line:181.0/2.0;181.0/20.0
line:181.0/20.0;1.0/20.0
line:1.0/20.0;1.0/2.0
fillColor:16711935
fillPolygon:0.0/0.0;0.0/0.0;0.0/0.0;0.0/0.0;
lineColor:4042322160
lineSize:1.4
line:0.0/0.0;0.0/0.0
line:0.0/0.0;0.0/0.0
line:0.0/0.0;0.0/0.0
line:0.0/0.0;0.0/0.0
fillColor:0
fillPolygon:363.0/6.0;363.0/15.0;3.0/15.0;3.0/6.0;
lineColor:16711695
lineSize:113.0
line:3.0/6.0;363.0/6.0
line:363.0/6.0;363.0/15.0
line:363.0/15.0;3.0/15.0
line:3.0/15.0;3.0/6.0
)");
				}
			}
		}
	}
}