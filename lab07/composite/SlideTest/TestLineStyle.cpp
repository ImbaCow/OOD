#include "pch.h"
#include "CLineStyle.h"
#include "CRectangleShape.h"
#include "TestUtils.h"

using namespace std;

SCENARIO("Line style can change properties")
{
	GIVEN("default line style")
	{
		CLineStyle style;

		REQUIRE_THROWS_AS(style.GetLineSize(), std::logic_error);

		WHEN("enable")
		{
			style.Enable(true);

			THEN("style line size is undefined")
			{
				CHECK_FALSE(style.GetLineSize().has_value());
			}

			AND_WHEN("set line size")
			{
				style.SetLineSize(1.2);

				THEN("line size is defined")
				{
					CHECK(style.GetLineSize().has_value());
					CHECK(style.GetLineSize().value() == 1.2);
				}
			}

			AND_WHEN("disable")
			{
				style.Enable(false);

				THEN("line size is undefined")
				{
					CHECK_THROWS_AS(style.GetLineSize(), std::logic_error);
				}
			}
		}
	}

	GIVEN("initialized line style")
	{
		CLineStyle style(0x00FF00F0, 3.5);

		REQUIRE(style.GetLineSize().has_value());
		REQUIRE(style.GetLineSize().value() == 3.5);

		WHEN("disable and then enable")
		{
			style.Enable(false);
			style.Enable(true);

			THEN("style line size is old value")
			{
				CHECK(style.GetLineSize().has_value());
				CHECK(style.GetLineSize().value() == 3.5);
			}
		}
	}
}

SCENARIO("Shape line style cannot be nullptr")
{
	GIVEN("nullptr style")
	{
		unique_ptr<ILineStyle> stylePtr = nullptr;

		THEN("shape initialization throw error")
		{
			CHECK_THROWS_AS(CRectangleShape({ { .0, .0 }, .0, .0 }, make_unique<CStyle>(), move(stylePtr)), std::invalid_argument);
		}
	}
}