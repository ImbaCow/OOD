#pragma once
#include "pch.h"
#include "CEllipseShape.h"
#include "TestUtils.h"
#include "TestCanvas.h"

using namespace Catch::Matchers::Floating;
using namespace std;

SCENARIO("Ellipse can be created and resized")
{
	GIVEN("A ellipse shape")
	{
		Point p1{ 10.0, 6.0 };
		CEllipseShape shape({ p1, 180.0, 9.0 }, make_shared<CStyle>(), make_shared<CLineStyle>());

		RequirePointEquality(shape.GetFrame().leftTop, { 10.0, 6.0 });
		RequireDoubleEquality(shape.GetFrame().width, 180.0);
		RequireDoubleEquality(shape.GetFrame().height, 9.0);

		WHEN("offset is moved and shape is resized")
		{
			shape.SetFrame({ { 150.0, 96.0 }, 90.0, 18.0 });
			THEN("ellipse is moved and resized")
			{
				CheckPointEquality(shape.GetLeftTop(), { 150.0, 96.0 });
				CheckDoubleEquality(shape.GetWidth(), 90.0);
				CheckDoubleEquality(shape.GetHeight(), 18.0);
			}
		}
	}

	GIVEN("A ellipse with 0 size")
	{
		Point p1{ .0, .0 };
		CEllipseShape shape({ p1, .0, .0 }, make_shared<CStyle>(), make_shared<CLineStyle>());

		RequirePointEquality(shape.GetFrame().leftTop, { .0, .0 });
		RequireDoubleEquality(shape.GetFrame().width, .0);
		RequireDoubleEquality(shape.GetFrame().height, .0);

		WHEN("offset is moved and shape is resized")
		{
			shape.SetFrame({ { 11.0, 12.0 }, 13.0, 14.0 });
			THEN("ellipse offset moved and shape is not resized")
			{
				CheckPointEquality(shape.GetLeftTop(), { 11.0, 12.0 });
				CheckDoubleEquality(shape.GetWidth(), 13.0);
				CheckDoubleEquality(shape.GetHeight(), 14.0);
			}
		}
	}
}

SCENARIO("Ellipse can be drawn")
{
	GIVEN("canvas")
	{
		std::ostringstream out;
		TestCanvas canvas(out);

		AND_GIVEN("filled ellipse")
		{
			Point p1{ 10.0, 6.0 };
			CEllipseShape shape({ p1, 180.0, 9.0 }, make_shared<CStyle>(0xFFFFFFFF), make_shared<CLineStyle>(0xFFFFFFFF, 1.2));

			std::ostringstream out;
			TestCanvas canvas(out);

			WHEN("call shape draw")
			{
				shape.Draw(canvas);

				THEN("canvas contain shape")
				{
					CHECK(out.str() == R"(fillColor:4294967295
fillEllipse:10.0/6.0;180.0;9.0
lineColor:4294967295
lineSize:1.2
ellipse:10.0/6.0;180.0;9.0
)");
				}
			}
		}
	}
}