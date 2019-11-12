#pragma once 
#include "pch.h"
#include "CTriangleShape.h"
#include "TestUtils.h"
#include "TestCanvas.h"

using namespace Catch::Matchers::Floating;
using namespace std;

SCENARIO("Triangle can be created and resized")
{
	GIVEN("A triangle shape")
	{
		Point p1{ 10.0, 12.0 };
		Point p2{ 110.0, 15.0 };
		Point p3{ 190.0, 6.0 };
		CTriangleShape shape(p1, p2, p3, make_shared<CStyle>(), make_shared<CLineStyle>());

		RequirePointEquality(shape.GetFrame().leftTop, { 10.0, 6.0 });
		RequireDoubleEquality(shape.GetFrame().width, 180.0);
		RequireDoubleEquality(shape.GetFrame().height, 9.0);

		WHEN("offset is moved and shape is resized")
		{
			shape.SetFrame({ { 150.0, 96.0 }, 90.0, 18.0 });
			THEN("triangle vertex moved")
			{
				CheckPointEquality(shape.GetVertex1(), { 150.0, 108.0 });
				CheckPointEquality(shape.GetVertex2(), { 200.0, 114.0 });
				CheckPointEquality(shape.GetVertex3(), { 240.0, 96.0 });
			}
		}
	}

	GIVEN("A triangle with 0 size")
	{
		Point p1{ .0, .0 };
		Point p2{ .0, .0 };
		Point p3{ .0, .0 };
		CTriangleShape shape(p1, p2, p3, make_shared<CStyle>(), make_shared<CLineStyle>());

		RequirePointEquality(shape.GetFrame().leftTop, { .0, .0 });
		RequireDoubleEquality(shape.GetFrame().width, .0);
		RequireDoubleEquality(shape.GetFrame().height, .0);

		WHEN("offset is moved and shape is not resized")
		{
			shape.SetFrame({ { 11.0, 12.0 }, 13.0, 14.0 });
			THEN("triangle offset moved and shape is not resized")
			{
				CheckPointEquality(shape.GetVertex1(), { 11.0, 12.0 });
				CheckPointEquality(shape.GetVertex2(), { 11.0, 12.0 });
				CheckPointEquality(shape.GetVertex3(), { 11.0, 12.0 });
			}
		}
	}
}

SCENARIO("Triangle can be drawn")
{
	GIVEN("canvas")
	{
		std::ostringstream out;
		TestCanvas canvas(out);

		AND_GIVEN("filled shape")
		{
			Point p1{ 10.0, 12.0 };
			Point p2{ 110.0, 15.0 };
			Point p3{ 190.0, 6.0 };
			CTriangleShape shape(p1, p2, p3, make_shared<CStyle>(0xFFFFFFFF), make_shared<CLineStyle>(0xFFFFFFFF, 1.2));

			WHEN("call shape draw")
			{
				shape.Draw(canvas);

				THEN("canvas contain shape")
				{
					CHECK(out.str() == R"(fillColor:4294967295
fillPolygon:10.0/12.0;110.0/15.0;190.0/6.0;
lineColor:4294967295
lineSize:1.2
line:10.0/12.0;110.0/15.0
line:110.0/15.0;190.0/6.0
line:190.0/6.0;10.0/12.0
)");
				}
			}
		}
	}
}