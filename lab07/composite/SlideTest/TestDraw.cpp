#include "pch.h"
#include "TestUtils.h"
#include "CEllipseShape.h"
#include "TestCanvas.h"

using namespace std;

SCENARIO("Shapes can be drawn")
{
	GIVEN("canvas")
	{
		std::ostringstream out;
		TestCanvas canvas(out);

		AND_GIVEN("no line style shape")
		{
			Point p1{ 10.0, 6.0 };
			CEllipseShape shape({ p1, 180.0, 9.0 }, make_unique<CStyle>(0xFFFFFFFF), make_unique<CLineStyle>());

			WHEN("call shape draw")
			{
				shape.Draw(canvas);

				THEN("canvas contain only fill style shape")
				{
					CHECK(out.str() == R"(fillColor:4294967295
fillEllipse:10.0/6.0;180.0;9.0
)");
				}
			}
		}

		AND_GIVEN("no fill style shape")
		{
			Point p1{ 10.0, 6.0 };
			CEllipseShape shape({ p1, 180.0, 9.0 }, make_unique<CStyle>(), make_unique<CLineStyle>(0xFFFFFFFF, 1.2));

			WHEN("call shape draw")
			{
				shape.Draw(canvas);

				THEN("canvas contain only line style shape")
				{
					CHECK(out.str() == R"(lineColor:4294967295
lineSize:1.2
ellipse:10.0/6.0;180.0;9.0
)");
				}
			}
		}

		AND_GIVEN("Enabled fill and line style shape")
		{
			Point p1{ 10.0, 6.0 };
			auto fillStyle = make_unique<CStyle>();
			auto lineStyle = make_unique<CLineStyle>();
			fillStyle->Enable(true);
			lineStyle->Enable(true);
			CEllipseShape shape({ p1, 180.0, 9.0 }, move(fillStyle), move(lineStyle));

			WHEN("call shape draw")
			{
				shape.Draw(canvas);

				THEN("canvas contain default styles shape")
				{
					CHECK(out.str() == R"(fillColor:0
fillEllipse:10.0/6.0;180.0;9.0
lineColor:0
lineSize:0.0
ellipse:10.0/6.0;180.0;9.0
)");
				}
			}
		}
	}
}