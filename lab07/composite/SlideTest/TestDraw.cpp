#include "pch.h"
#include "TestUtils.h"
#include "CEllipseShape.h"
#include "TestCanvas.h"

using namespace std;

SCENARIO("Shapes can be drawn")
{
	GIVEN("canvas")
	{
		AND_GIVEN("no line style shape")
		{
			Point p1{ 10.0, 6.0 };
			CEllipseShape shape({ p1, 180.0, 9.0 }, make_shared<CStyle>(0xFFFFFFFF), make_shared<CLineStyle>());

			std::ostringstream out;
			TestCanvas canvas(out);

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
			CEllipseShape shape({ p1, 180.0, 9.0 }, make_shared<CStyle>(), make_shared<CLineStyle>(0xFFFFFFFF, 1.2));

			std::ostringstream out;
			TestCanvas canvas(out);

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
			auto fillStyle = make_shared<CStyle>();
			auto lineStyle = make_shared<CLineStyle>();
			fillStyle->Enable(true);
			lineStyle->Enable(true);
			CEllipseShape shape({ p1, 180.0, 9.0 }, fillStyle, lineStyle);

			std::ostringstream out;
			TestCanvas canvas(out);

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